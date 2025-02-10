use crate::{config::text_replacement::TextReplacement, error::GpmError};
use anyhow::Context;
use globset::{Glob, GlobSetBuilder};
use serde::{Deserialize, Serialize};
use std::path::{Path, PathBuf};

use super::submit::SubmitConfig;

#[derive(Debug, Serialize, Deserialize)]
pub struct PushConfiguration {
    pub project: ProjectInfo,
    pub submit: SubmitConfig,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct ProjectInfo {
    pub name: String,
    pub version: String,
}

pub struct PushConfigManager;

impl PushConfigManager {
    pub fn new() -> Self {
        Self
    }

    pub fn load_push_config(&self, project_path: &Path) -> anyhow::Result<PushConfiguration> {
        let config_path = project_path.join("push.toml");
        if !config_path.exists() {
            return Err(GpmError::ConfigError(format!(
                "push.toml not found in {}",
                project_path.display()
            ))
            .into());
        }

        let content = std::fs::read_to_string(&config_path).context("Failed to read push.toml")?;

        let config: PushConfiguration =
            toml::from_str(&content).context("Failed to parse push.toml")?;

        self.validate_config(&config, project_path)?;

        Ok(config)
    }

    fn validate_config(
        &self,
        config: &PushConfiguration,
        project_path: &Path,
    ) -> anyhow::Result<()> {
        // Validate file patterns
        if config.submit.files.is_empty() {
            return Err(GpmError::ConfigError("No files specified in push.toml".into()).into());
        }

        // Validate function paths if GPM is enabled
        config.submit.preprocessor.validate(project_path)?;

        // Validate hooks if present
        if let Some(pre_submit) = &config.submit.hooks.pre_submit {
            if pre_submit.trim().is_empty() {
                return Err(GpmError::ConfigError("Empty pre-submit hook".into()).into());
            }
        }

        if let Some(post_submit) = &config.submit.hooks.post_submit {
            if post_submit.trim().is_empty() {
                return Err(GpmError::ConfigError("Empty post-submit hook".into()).into());
            }
        }

        Ok(())
    }

    pub fn get_included_files(
        &self,
        config: &PushConfiguration,
        base_path: &Path,
    ) -> anyhow::Result<Vec<PathBuf>> {
        let mut builder = GlobSetBuilder::new();
        for pattern in &config.submit.files {
            builder.add(Glob::new(pattern)?);
        }
        let include_set = builder.build()?;

        let exclude_set = if let Some(excludes) = &config.submit.exclude {
            let mut builder = GlobSetBuilder::new();
            for pattern in excludes {
                builder.add(Glob::new(pattern)?);
            }
            Some(builder.build()?)
        } else {
            None
        };

        let mut included = Vec::new();
        for entry in walkdir::WalkDir::new(base_path) {
            let entry = entry?;
            let path = entry.path();
            if path.is_file() {
                let relative_path = path.strip_prefix(base_path)?;
                if include_set.is_match(relative_path) {
                    if let Some(exclude_set) = &exclude_set {
                        if !exclude_set.is_match(relative_path) {
                            included.push(path.to_path_buf());
                        }
                    } else {
                        included.push(path.to_path_buf());
                    }
                }
            }
        }

        Ok(included)
    }

    // Implementation of copy function
    pub fn copy_additional_files(
        &self,
        config: &PushConfiguration,
        source_base: &Path,
        target_base: &Path,
    ) -> anyhow::Result<()> {
        let gpm_processor = crate::processor::gpm::GpmProcessor::new();

        // Helper function to process and copy a single file
        fn process_and_copy(
            source: &Path,
            target: &Path,
            replacements: &[TextReplacement],
            config: &PushConfiguration,
            gpm_processor: &crate::processor::gpm::GpmProcessor,
            should_process_gpm: bool,
        ) -> anyhow::Result<()> {
            // Create parent directories if needed
            if let Some(parent) = target.parent() {
                std::fs::create_dir_all(parent)?;
            }

            // Read file content
            let mut content = std::fs::read_to_string(source)?;

            // Apply all text replacements
            for replacement in replacements {
                content = content.replace(&replacement.find, &replacement.replace_with);
            }

            // Write to a temporary file for GPM processing if needed
            if should_process_gpm && config.submit.preprocessor.enable_gpm {
                let temp_dir = tempfile::tempdir()?;
                let temp_file = temp_dir.path().join("temp_file");
                std::fs::write(&temp_file, content)?;

                // Process with GPM
                gpm_processor.process_file(&temp_file, target, &config.submit.preprocessor)?;
            } else {
                // Write directly if no GPM processing needed
                std::fs::write(target, content)?;
            }

            log::debug!(
                "Processed and copied {} to {}",
                source.display(),
                target.display()
            );
            Ok(())
        }

        // Rest of the implementation remains the same, but use process_and_copy instead
        for copy_config in &config.submit.copy {
            // Handle both absolute and relative source paths
            let source_path = if Path::new(&copy_config.source).is_absolute() {
                PathBuf::from(&copy_config.source)
            } else {
                if copy_config.source.starts_with("../") {
                    source_base
                        .parent()
                        .ok_or_else(|| anyhow::anyhow!("Cannot resolve parent directory"))?
                        .join(copy_config.source.strip_prefix("../").unwrap())
                } else {
                    source_base.join(&copy_config.source)
                }
            };

            // Get the concrete file path if it exists
            if source_path.exists() {
                let target_path = if let Some(dest) = &copy_config.destination {
                    target_base.join(dest).join(
                        source_path
                            .file_name()
                            .ok_or_else(|| anyhow::anyhow!("Invalid file name"))?,
                    )
                } else {
                    target_base.join(
                        source_path
                            .file_name()
                            .ok_or_else(|| anyhow::anyhow!("Invalid file name"))?,
                    )
                };

                process_and_copy(
                    &source_path,
                    &target_path,
                    &copy_config.replace,
                    config,
                    &gpm_processor,
                    self.should_process_with_gpm(&source_path),
                )?;
            } else {
                // Handle glob patterns...
                let pattern = if copy_config.source.starts_with("../") {
                    let parent = source_base
                        .parent()
                        .ok_or_else(|| anyhow::anyhow!("Cannot resolve parent directory"))?;
                    parent.join(copy_config.source.strip_prefix("../").unwrap())
                } else {
                    source_base.join(&copy_config.source)
                };

                let glob = globset::Glob::new(
                    pattern
                        .to_str()
                        .ok_or_else(|| anyhow::anyhow!("Invalid path: {}", pattern.display()))?,
                )?;
                let matcher = glob.compile_matcher();

                // Define base directory for glob search
                let search_base = if copy_config.source.starts_with("../") {
                    source_base
                        .parent()
                        .ok_or_else(|| anyhow::anyhow!("Cannot resolve parent directory"))?
                        .to_path_buf()
                } else {
                    source_base.to_path_buf()
                };

                // Walk through source directory
                let mut found_matches = false;
                for entry in walkdir::WalkDir::new(&search_base) {
                    let entry = entry?;
                    if !entry.file_type().is_file() {
                        continue;
                    }

                    let relative_path = entry
                        .path()
                        .strip_prefix(&search_base)?
                        .to_string_lossy()
                        .into_owned();

                    if matcher.is_match(&relative_path) {
                        found_matches = true;
                        let source_path = entry.path();
                        let target_path = if let Some(dest) = &copy_config.destination {
                            if copy_config.flatten {
                                target_base.join(dest).join(
                                    source_path
                                        .file_name()
                                        .ok_or_else(|| anyhow::anyhow!("Invalid file name"))?,
                                )
                            } else {
                                target_base.join(dest).join(&relative_path)
                            }
                        } else {
                            target_base.join(&relative_path)
                        };

                        process_and_copy(
                            source_path,
                            &target_path,
                            &copy_config.replace,
                            config,
                            &gpm_processor,
                            self.should_process_with_gpm(source_path),
                        )?;
                    }
                }

                if !found_matches {
                    log::warn!(
                        "No files matched pattern: {} (searched in {})",
                        copy_config.source,
                        search_base.display()
                    );
                }
            }
        }

        Ok(())
    }

    fn should_process_with_gpm(&self, path: &Path) -> bool {
        matches!(path.extension().and_then(|s| s.to_str()), Some("c" | "h"))
            || matches!(
                path.file_name().and_then(|s| s.to_str()),
                Some("Makefile" | "makefile")
            )
    }
}
