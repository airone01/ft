use std::path::{Path, PathBuf};
use std::process::Command as ProcessCommand;

use crate::config::push::{PushConfigManager, PushConfiguration};
use crate::processor::gpm::GpmProcessor;
use crate::Command;

use anyhow::Context;
use crossterm::style::Stylize;
use log::{debug, info, trace};
use tempfile::TempDir;

pub struct Submit {
    project_name: String,
    target_repo: String,
    push_config: Option<PushConfiguration>,
    cwd: PathBuf,
}

impl Submit {
    pub fn new(project_name: &str, target_repo: &str, cwd: PathBuf) -> Self {
        Self {
            project_name: project_name.to_string(),
            target_repo: target_repo.to_string(),
            push_config: None,
            cwd,
        }
    }

    fn setup_git_repo(&self, dir: &Path, target_repo: &str) -> anyhow::Result<()> {
        // Initialize repository
        let status = ProcessCommand::new("git")
            .arg("init")
            .current_dir(dir)
            .status()
            .context("Failed to initialize git repository")?;
        if !status.success() {
            return Err(anyhow::anyhow!("Failed to initialize git repository"));
        }

        // Configure git for this repository
        let status = ProcessCommand::new("git")
            .args(["config", "user.name", "Git Project Manager"])
            .current_dir(dir)
            .status()
            .context("Failed to set git user name")?;
        if !status.success() {
            return Err(anyhow::anyhow!("Failed to set git user name"));
        }

        let status = ProcessCommand::new("git")
            .args(["config", "user.email", "gpm@doesnt.exist"])
            .current_dir(dir)
            .status()
            .context("Failed to set git user email")?;
        if !status.success() {
            return Err(anyhow::anyhow!("Failed to set git user email"));
        }

        // Add all files
        let status = ProcessCommand::new("git")
            .args(["add", "."])
            .current_dir(dir)
            .status()
            .context("Failed to add files to git")?;
        if !status.success() {
            return Err(anyhow::anyhow!("Failed to add files to git"));
        }

        // Create commit
        let status = ProcessCommand::new("git")
            .args([
                "commit",
                "-m",
                &format!(r"chore(gpm): submission of {}", self.project_name),
            ])
            .current_dir(dir)
            .status()
            .context("Failed to create commit")?;
        if !status.success() {
            return Err(anyhow::anyhow!("Failed to create commit"));
        }

        // Add remote
        let status = ProcessCommand::new("git")
            .args(["remote", "add", "origin", target_repo])
            .current_dir(dir)
            .status()
            .context("Failed to add remote")?;
        if !status.success() {
            return Err(anyhow::anyhow!("Failed to add remote"));
        }

        // Force push
        debug!("Pushing to remote...");
        let status = ProcessCommand::new("git")
            .args(["push", "-f", "origin", "HEAD:main"])
            .current_dir(dir)
            .status()
            .context("Failed to push to remote")?;
        if !status.success() {
            return Err(anyhow::anyhow!("Failed to push to remote"));
        }

        Ok(())
    }

    fn prepare_submission(&mut self) -> anyhow::Result<TempDir> {
        // Resolve project path relative to cwd
        let project_path = self.cwd.join(&self.project_name);

        // Load push.toml configuration
        let config_manager = PushConfigManager::new();
        let push_config = config_manager.load_push_config(&project_path)?;

        // Create temporary directory for processed files
        let temp_dir = TempDir::new()?;
        let processor = GpmProcessor::new();

        // Get files to include based on push.toml configuration
        let files = config_manager.get_included_files(&push_config, &project_path)?;

        // Process each file
        for file in files {
            let relative_path = file.strip_prefix(&project_path)?;
            let output_path = temp_dir.path().join(relative_path);

            // Create parent directories if needed
            if let Some(parent) = output_path.parent() {
                std::fs::create_dir_all(parent)?;
            }

            // Process or copy the file
            if push_config.submit.preprocessor.enable_gpm
                && (matches!(file.extension().and_then(|s| s.to_str()), Some("c" | "h"))
                    || file.file_name().and_then(|s| s.to_str()) == Some("Makefile")
                    || file.file_name().and_then(|s| s.to_str()) == Some("makefile"))
            {
                trace!("Applying potential GPM processing to {}", file.display());
                processor.process_file(&file, &output_path, &push_config.submit.preprocessor)?;
            } else {
                trace!("Copying file without processing: {}", file.display());
                std::fs::copy(&file, &output_path)?;
            }
        }

        // Copy additional files as specified in the configuration
        config_manager.copy_additional_files(&push_config, &project_path, temp_dir.path())?;

        // Store push_config for use in execute
        self.push_config = Some(push_config);

        Ok(temp_dir)
    }

    fn run_hook(&self, command: &str) -> anyhow::Result<()> {
        info!("{} {}", "Running hook:".blue(), command);

        let status = ProcessCommand::new("sh")
            .arg("-c")
            .arg(command)
            .status()
            .context("Failed to execute hook")?;

        if !status.success() {
            return Err(anyhow::anyhow!("Hook failed: {}", command));
        }

        Ok(())
    }
}

impl Command for Submit {
    fn execute(&mut self) -> anyhow::Result<()> {
        let project_path = self.cwd.join(&self.project_name);

        let config_manager = PushConfigManager::new();
        let push_config = config_manager.load_push_config(&project_path)?;

        // Run pre-submit hook if configured
        if let Some(pre_hook) = &push_config.submit.hooks.pre_submit {
            self.run_hook(pre_hook)?;
        }

        // Prepare submission files
        let temp_dir = self.prepare_submission()?;

        // Setup git repo and push
        self.setup_git_repo(temp_dir.path(), &self.target_repo)?;

        // Run post-submit hook if configured
        if let Some(post_hook) = &push_config.submit.hooks.post_submit {
            self.run_hook(post_hook)?;
        }

        info!("Project submitted successfully!");
        Ok(())
    }
}
