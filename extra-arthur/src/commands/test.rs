use crate::config::push::PushConfigManager;
use crate::config::Config;
use crate::processor::gpm::GpmProcessor;
use crate::Command;
use crossterm::style::Stylize;
use std::path::PathBuf;
use std::process::Command as ProcessCommand;
use tempfile::TempDir;

pub struct Test {
    project_name: String,
    config: Config,
}

struct ValidationResults {
    norminette: Option<bool>,
    make_test: Option<bool>,
}

impl Test {
    pub fn new(project_name: &str) -> Self {
        Self {
            project_name: project_name.to_string(),
            config: Config::load().expect("Failed to load config"),
        }
    }

    fn prepare_test(&self) -> anyhow::Result<PathBuf> {
        let project_path = self
            .config
            .get_project_path(&self.project_name)
            .ok_or_else(|| anyhow::anyhow!("Project not found"))?;

        // Load push.toml configuration
        let config_manager = PushConfigManager::new();
        let push_config = config_manager.load_push_config(project_path)?;

        println!("{}", "📋 Testing configuration loaded successfully".blue());

        // Create temporary directory for processed files
        let temp_dir = TempDir::new()?;
        let processor = GpmProcessor::new();

        // Get files to include based on push.toml configuration
        let files = config_manager.get_included_files(&push_config, project_path)?;

        println!("{} {} files selected for testing", "📦".blue(), files.len());

        // Process each file
        for file in files {
            let relative_path = file.strip_prefix(project_path)?;
            let output_path = temp_dir.path().join(relative_path);

            println!("{} Processing: {}", "🔄".blue(), relative_path.display());

            // Create parent directories if needed
            if let Some(parent) = output_path.parent() {
                std::fs::create_dir_all(parent)?;
            }

            // Process or copy the file
            if push_config.submit.preprocessor.enable_gpm
                && matches!(file.extension().and_then(|s| s.to_str()), Some("c" | "h"))
            {
                processor.process_file(&file, &output_path, &push_config.submit.preprocessor)?;
                println!("{} GPM directives processed", "✓".green());
            } else {
                std::fs::copy(&file, &output_path)?;
                println!("{} File copied", "✓".green());
            }
        }

        // Run validations if configured
        if push_config.submit.validation.norminette || push_config.submit.validation.make_test {
            let validation_results = self.run_validations(
                &temp_dir.path(),
                push_config.submit.validation.norminette,
                push_config.submit.validation.make_test,
            )?;

            self.print_validation_results(&validation_results);
        }

        Ok(temp_dir.path().to_path_buf())
    }

    fn run_validations(
        &self,
        test_dir: &std::path::Path,
        run_norminette: bool,
        run_make_test: bool,
    ) -> anyhow::Result<ValidationResults> {
        let mut results = ValidationResults {
            norminette: None,
            make_test: None,
        };

        if run_norminette {
            println!("{}", "\n🔍 Running Norminette...".blue());
            let output = ProcessCommand::new("norminette")
                .current_dir(test_dir)
                .output();

            results.norminette = match output {
                Ok(output) => Some(output.status.success()),
                Err(_) => {
                    println!("{}", "⚠️  Norminette not found in PATH".yellow());
                    None
                }
            };
        }

        if run_make_test {
            println!("{}", "\n🔨 Running Make test...".blue());
            let output = ProcessCommand::new("make")
                .arg("test")
                .current_dir(test_dir)
                .output();

            results.make_test = match output {
                Ok(output) => Some(output.status.success()),
                Err(_) => {
                    println!("{}", "⚠️  Make test failed to execute".yellow());
                    None
                }
            };
        }

        Ok(results)
    }

    fn print_validation_results(&self, results: &ValidationResults) {
        println!("\n{}", "📊 Validation Results:".blue());

        if let Some(norminette_result) = results.norminette {
            let status = if norminette_result {
                "✅ Passed".green()
            } else {
                "❌ Failed".red()
            };
            println!("   Norminette: {}", status);
        }

        if let Some(make_test_result) = results.make_test {
            let status = if make_test_result {
                "✅ Passed".green()
            } else {
                "❌ Failed".red()
            };
            println!("   Make test: {}", status);
        }
    }
}

impl Command for Test {
    fn execute(&mut self) -> anyhow::Result<()> {
        println!("{}", "🧪 Starting test process...".blue());

        let test_dir = self.prepare_test()?;

        println!("\n{}", "📁 Test files prepared in:".blue());
        println!("   {}", test_dir.display());

        println!("\n{}", "✨ Test process completed successfully!".green());
        println!(
            "{}",
            "   Review the files in the test directory above.".blue()
        );
        Ok(())
    }
}
