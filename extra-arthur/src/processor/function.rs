use crate::processor::FunctionExtractor as FunctionExtractorTrait;
use anyhow::Context;
use regex::Regex;
use std::fs;
use std::path::PathBuf;
use walkdir::WalkDir;

#[derive(Debug)]
pub struct FunctionExtractor {
    begin_regex: Regex,
    end_regex: Regex,
}

impl Default for FunctionExtractor {
    fn default() -> Self {
        Self::new()
    }
}

impl FunctionExtractor {
    pub fn new() -> Self {
        Self {
            begin_regex: Regex::new(r"(?://|#)\s*GPM\?\s*begin\s+([a-zA-Z0-9_]+)\s*$").unwrap(),
            end_regex: Regex::new(r"(?://|#)\s*GPM\?\s*end\s+([a-zA-Z0-9_]+)\s*$").unwrap(),
        }
    }
}

impl FunctionExtractorTrait for FunctionExtractor {
    fn find_function(
        &self,
        name: &str,
        search_paths: &[PathBuf],
    ) -> anyhow::Result<Option<String>> {
        for path in search_paths {
            log::debug!("Searching for function {} in {}", name, path.display());
            for entry in WalkDir::new(path).follow_links(true) {
                let entry = entry.context("Failed to read directory entry")?;
                let path = entry.path();

                if matches!(path.extension().and_then(|s| s.to_str()), Some("c") | Some("h") | Some("cpp") | Some("mk")) || path.file_name().and_then(|s| s.to_str()) == Some("Makefile") {
                    log::debug!("Checking file: {}", path.display());
                    match fs::read_to_string(path) {
                        Ok(content) => {
                            if let Some(func_content) = self.extract_function(&content, name) {
                                log::info!("Found function {} in {}", name, path.display());
                                return Ok(Some(func_content));
                            }
                        }
                        Err(e) => {
                            log::warn!("Failed to read {}: {}", path.display(), e);
                            continue;
                        }
                    }
                }
            }
        }
        Ok(None)
    }

    fn extract_function(&self, content: &str, name: &str) -> Option<String> {
        let mut lines = content.lines();
        let mut capturing = false;
        let mut result = String::new();

        while let Some(line) = lines.next() {
            if !capturing {
                if let Some(captures) = self.begin_regex.captures(line) {
                    if captures.get(1).unwrap().as_str() == name {
                        capturing = true;
                    }
                }
            } else {
                if let Some(captures) = self.end_regex.captures(line) {
                    if captures.get(1).unwrap().as_str() == name {
                        return Some(result);
                    }
                } else {
                    result.push_str(line);
                    result.push('\n');
                }
            }
        }
        None
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::fs;
    use tempfile::TempDir;

    fn setup_test_directory() -> anyhow::Result<TempDir> {
        let temp_dir = TempDir::new()?;

        // Create a multi-file test structure
        let files = vec![
            (
                "file1.c",
                r#"
// Some header
// GPM? begin test_func1
void test_func1(void)
{
    printf("test1\n");
}
// GPM? end test_func1
            "#,
            ),
            (
                "subdir/file2.c",
                r#"
// GPM? begin test_func2
void test_func2(void)
{
    printf("test2\n");
}
// GPM? end test_func2
            "#,
            ),
            (
                "file3.c",
                r#"
// Malformed markers
// GPM? begin test_func3
void test_func3(void)
{
    printf("test3\n");
// Missing end marker
            "#,
            ),
        ];

        for (path, content) in files {
            let full_path = temp_dir.path().join(path);
            if let Some(parent) = full_path.parent() {
                fs::create_dir_all(parent)?;
            }
            fs::write(full_path, content)?;
        }

        Ok(temp_dir)
    }

    #[test]
    fn test_function_extraction_success() -> anyhow::Result<()> {
        let temp_dir = setup_test_directory()?;
        let extractor = FunctionExtractor::new();

        // Test finding function in root directory
        let func1 = extractor.find_function("test_func1", &[temp_dir.path().to_path_buf()])?;
        assert!(func1.is_some());
        assert!(func1.unwrap().contains("void test_func1(void)"));

        // Test finding function in subdirectory
        let func2 = extractor.find_function("test_func2", &[temp_dir.path().to_path_buf()])?;
        assert!(func2.is_some());
        assert!(func2.unwrap().contains("void test_func2(void)"));

        Ok(())
    }

    #[test]
    fn test_function_extraction_failure() -> anyhow::Result<()> {
        let temp_dir = setup_test_directory()?;
        let extractor = FunctionExtractor::new();

        // Test non-existent function
        let result =
            extractor.find_function("nonexistent_func", &[temp_dir.path().to_path_buf()])?;
        assert!(result.is_none());

        // Test malformed markers
        let result = extractor.find_function("test_func3", &[temp_dir.path().to_path_buf()])?;
        assert!(result.is_none());

        Ok(())
    }

    #[test]
    fn test_glob_pattern_matching() -> anyhow::Result<()> {
        use globset::{Glob, GlobSetBuilder};

        let temp_dir = TempDir::new()?;

        // Create test files
        let files = vec![
            "src/main.c",
            "src/utils.c",
            "src/test_main.c",
            "include/header.h",
            "README.md",
        ];

        for file in &files {
            let path = temp_dir.path().join(file);
            if let Some(parent) = path.parent() {
                fs::create_dir_all(parent)?;
            }
            fs::write(path, "")?;
        }

        // Test include patterns
        let mut builder = GlobSetBuilder::new();
        builder.add(Glob::new("src/*.c")?);
        builder.add(Glob::new("include/*.h")?);
        let include_set = builder.build()?;

        // Test exclude patterns
        let mut builder = GlobSetBuilder::new();
        builder.add(Glob::new("src/test_*.c")?);
        let exclude_set = builder.build()?;

        let mut included = Vec::new();
        for entry in walkdir::WalkDir::new(temp_dir.path()) {
            let entry = entry?;
            let path = entry.path();
            if path.is_file() {
                let relative_path = path.strip_prefix(temp_dir.path())?;
                if include_set.is_match(relative_path) && !exclude_set.is_match(relative_path) {
                    included.push(relative_path.to_path_buf());
                }
            }
        }

        assert_eq!(included.len(), 3); // main.c, utils.c, and header.h
        assert!(included.iter().any(|p| p.to_str() == Some("src/main.c")));
        assert!(included.iter().any(|p| p.to_str() == Some("src/utils.c")));
        assert!(included
            .iter()
            .any(|p| p.to_str() == Some("include/header.h")));
        assert!(!included
            .iter()
            .any(|p| p.to_str() == Some("src/test_main.c")));

        Ok(())
    }
}
