use super::function::FunctionExtractor;
use crate::config::push::PreprocessorConfig;
use crate::error::GpmError;
use crate::processor::{FileProcessor, FunctionExtractor as FunctionExtractorTrait};
use regex::Regex;
use std::fs;
use std::path::{Path, PathBuf};

pub struct GpmProcessor {
    gpm_directive_regex: Regex,
    gpm_remove_regex: Regex,
    gpm_strip_comment_regex: Regex,
    function_extractor: FunctionExtractor,
}

impl Default for GpmProcessor {
    fn default() -> Self {
        Self::new()
    }
}

impl GpmProcessor {
    pub fn new() -> Self {
        Self {
            gpm_directive_regex: Regex::new(r"(?://|#)\s*GPM:\s*([a-zA-Z0-9_]+)\s*$").unwrap(),
            gpm_remove_regex: Regex::new(r"(?://|#)\s*GPM!\s*$").unwrap(),
            gpm_strip_comment_regex: Regex::new(r"(?://|#)\s*GPM@\s*(.+)$").unwrap(),
            function_extractor: FunctionExtractor::new(),
        }
    }

    pub fn process_file(
        &self,
        input: &Path,
        output: &Path,
        config: &PreprocessorConfig,
    ) -> anyhow::Result<()> {
        let content = fs::read_to_string(input)
            .map_err(|e| GpmError::ProcessingError(format!("Failed to read input file: {}", e)))?;

        let processed = self.process_content(&content, &config.function_paths)?;

        fs::write(output, processed).map_err(|e| {
            GpmError::ProcessingError(format!("Failed to write output file: {}", e))
        })?;

        Ok(())
    }

    fn process_content(&self, content: &str, search_paths: &[PathBuf]) -> anyhow::Result<String> {
        let mut result = String::new();
        let mut lines = content.lines();

        while let Some(line) = lines.next() {
            // Skip GPM! lines
            if self.gpm_remove_regex.is_match(line) {
                continue;
            }

            // Process GPM: directives
            if let Some(captures) = self.gpm_directive_regex.captures(line) {
                let func_name = captures.get(1).unwrap().as_str();
                if let Some(func_content) = self
                    .function_extractor
                    .find_function(func_name, search_paths)?
                {
                    result.push_str(&func_content);
                } else {
                    return Err(GpmError::ProcessingError(format!(
                        "Function '{}' not found in any search path",
                        func_name
                    ))
                        .into());
                }
            } else if let Some(captures) = self.gpm_strip_comment_regex.captures(line) {
                // For GPM@ directives, only keep the content after GPM@
                let content = captures.get(1).unwrap().as_str();
                result.push_str(content);
                result.push('\n');
            } else {
                result.push_str(line);
                result.push('\n');
            }
        }

        Ok(result)
    }
}

impl FileProcessor for GpmProcessor {
    fn process_file(&self, input: &Path, output: &Path) -> anyhow::Result<()> {
        let content = fs::read_to_string(input)
            .map_err(|e| GpmError::ProcessingError(format!("Failed to read input file: {}", e)))?;

        let config = PreprocessorConfig {
            enable_gpm: true,
            function_paths: vec![],
        };

        let processed = self.process_content(&content, &config.function_paths)?;

        fs::write(output, processed).map_err(|e| {
            GpmError::ProcessingError(format!("Failed to write output file: {}", e))
        })?;

        Ok(())
    }

    fn process_directory(&self, input: &Path, output: &Path) -> anyhow::Result<()> {
        for entry in walkdir::WalkDir::new(input) {
            let entry = entry?;
            let path = entry.path();
            if path.is_file() {
                let relative_path = path.strip_prefix(input)?;
                let output_path = output.join(relative_path);

                if let Some(parent) = output_path.parent() {
                    fs::create_dir_all(parent)?;
                }

                let config = PreprocessorConfig {
                    enable_gpm: true,
                    function_paths: vec![],
                };

                match path.extension().and_then(|s| s.to_str()) {
                    Some("c" | "h" | "Makefile" | "makefile") => self.process_file(path, &output_path, &config)?,
                    _ => {
                        fs::copy(path, &output_path)?;
                    }
                };
            }
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::fs;
    use tempfile::TempDir;

    #[test]
    fn test_gpm_strip_comment() -> anyhow::Result<()> {
        let processor = GpmProcessor::new();
        let content = r#"int main(void)
{
    // GPM@ This comment text will be preserved
    # GPM@ Another preserved text
    // Normal comment stays
    return (0);
}
"#;
        let processed = processor.process_content(content, &[])?;
        assert!(processed.contains("This comment text will be preserved"));
        assert!(processed.contains("Another preserved text"));
        assert!(processed.contains("// Normal comment stays"));
        assert!(!processed.contains("GPM@"));
        assert!(!processed.contains("//") || !processed.contains("#"));
        Ok(())
    }

    #[test]
    fn test_gpm_remove() -> anyhow::Result<()> {
        let processor = GpmProcessor::new();
        let content = r#"int main(void) {
    // Some code
    return (0); // GPM!
}
"#;
        let processed = processor.process_content(content, &[])?;
        assert!(!processed.contains("GPM!"));
        Ok(())
    }

    #[test]
    fn test_function_extraction() -> anyhow::Result<()> {
        let temp_dir = TempDir::new()?;
        let func_path = temp_dir.path().join("test_func.c");

        let func_content = r#"
// Some header
// GPM? begin test_func
void test_func(void)
{
    printf("test\n");
}
// GPM? end test_func
// Some footer
"#;
        fs::write(&func_path, func_content)?;

        let extractor = FunctionExtractor::new();
        let content = fs::read_to_string(&func_path)?;
        let extracted = extractor.extract_function(&content, "test_func").unwrap();

        assert!(extracted.contains("void test_func(void)"));
        assert!(!extracted.contains("// Some header"));
        assert!(!extracted.contains("// Some footer"));

        Ok(())
    }

    #[test]
    fn test_gpm_function_insertion() -> anyhow::Result<()> {
        let temp_dir = TempDir::new()?;
        let func_path = temp_dir.path().join("example.c");

        // Create a test function file
        let func_content = r#"
// GPM? begin ft_example
void ft_example(void)
{
    printf("example\n");
}
// GPM? end ft_example
"#;
        fs::write(&func_path, func_content)?;

        let processor = GpmProcessor::new();
        let content = "int main(void)\n{\n    // GPM: ft_example\n    return (0);\n}\n";

        let processed = processor.process_content(content, &[temp_dir.path().to_path_buf()])?;

        assert!(processed.contains("void ft_example(void)"));
        assert!(processed.contains("return (0);"));

        Ok(())
    }
}
