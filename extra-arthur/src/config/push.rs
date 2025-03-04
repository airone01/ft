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

    // Implementation of copy function with improved glob handling
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

        // Helper function to copy an entire directory
        fn copy_directory(
            source_dir: &Path,
            target_dir: &Path,
            replacements: &[TextReplacement],
            config: &PushConfiguration,
            gpm_processor: &crate::processor::gpm::GpmProcessor,
            should_process_gpm_fn: &dyn Fn(&Path) -> bool,
        ) -> anyhow::Result<()> {
            // Create target directory if it doesn't exist
            std::fs::create_dir_all(target_dir)?;

            // Walk through the directory
            for entry in walkdir::WalkDir::new(source_dir) {
                let entry = entry?;
                let source_path = entry.path();

                // Calculate relative path from source directory
                let relative_path = source_path.strip_prefix(source_dir)?;
                let target_path = target_dir.join(relative_path);

                if source_path.is_file() {
                    // Process and copy each file
                    process_and_copy(
                        source_path,
                        &target_path,
                        replacements,
                        config,
                        gpm_processor,
                        should_process_gpm_fn(source_path),
                    )?;
                } else if source_path.is_dir() && source_path != source_dir {
                    // Just create the directory (files will be handled individually)
                    std::fs::create_dir_all(&target_path)?;
                }
            }

            log::debug!(
                "Copied directory {} to {}",
                source_dir.display(),
                target_dir.display()
            );
            Ok(())
        }

        for copy_config in &config.submit.copy {
            // Check if the pattern contains wildcards
            let has_wildcards = copy_config.source.contains('*');

            // Resolve the base path and glob pattern
            let (search_base, pattern_str) = if copy_config.source.starts_with("../") {
                // For patterns with parent directory references
                let parent = source_base
                    .parent()
                    .ok_or_else(|| anyhow::anyhow!("Cannot resolve parent directory"))?;

                if has_wildcards {
                    // Split at the directory containing wildcards
                    let path_parts: Vec<&str> = copy_config.source.split('/').collect();
                    let wild_idx = path_parts
                        .iter()
                        .position(|p| p.contains('*'))
                        .unwrap_or(path_parts.len() - 1);

                    // Base path is everything before the wildcard part
                    let base_parts = &path_parts[..wild_idx];
                    let pattern_parts = &path_parts[wild_idx..];

                    let mut base_path = parent.to_path_buf();
                    for part in base_parts.iter().skip(1) {
                        // skip the ".." part
                        base_path = base_path.join(part);
                    }

                    let pattern = pattern_parts.join("/");
                    (base_path, pattern)
                } else {
                    // No wildcards, use the exact path
                    let path = copy_config.source.strip_prefix("../").unwrap();
                    (parent.to_path_buf(), path.to_string())
                }
            } else if has_wildcards {
                // For normal paths with wildcards
                let path_parts: Vec<&str> = copy_config.source.split('/').collect();
                let wild_idx = path_parts
                    .iter()
                    .position(|p| p.contains('*'))
                    .unwrap_or(path_parts.len() - 1);

                let base_parts = &path_parts[..wild_idx];
                let pattern_parts = &path_parts[wild_idx..];

                let base_path = if base_parts.is_empty() {
                    source_base.to_path_buf()
                } else {
                    let base_path_str = base_parts.join("/");
                    source_base.join(base_path_str)
                };

                let pattern = pattern_parts.join("/");
                (base_path, pattern)
            } else {
                // Normal path without wildcards
                (source_base.to_path_buf(), copy_config.source.clone())
            };

            log::debug!(
                "Resolved search base: {}, pattern: {}",
                search_base.display(),
                pattern_str
            );

            // Handle concrete file/directory path
            let concrete_path = search_base.join(&pattern_str);
            if !has_wildcards && concrete_path.exists() {
                let target_path = if let Some(dest) = &copy_config.destination {
                    if concrete_path.is_file() {
                        // For files, append the filename to the destination path
                        target_base.join(dest).join(
                            concrete_path
                                .file_name()
                                .ok_or_else(|| anyhow::anyhow!("Invalid file name"))?,
                        )
                    } else {
                        // For directories, use the destination path directly
                        target_base.join(dest)
                    }
                } else {
                    if concrete_path.is_file() {
                        // For files without explicit destination, place at target root
                        target_base.join(
                            concrete_path
                                .file_name()
                                .ok_or_else(|| anyhow::anyhow!("Invalid file name"))?,
                        )
                    } else {
                        // For directories without explicit destination, use the directory name
                        target_base.join(
                            concrete_path
                                .file_name()
                                .ok_or_else(|| anyhow::anyhow!("Invalid directory name"))?,
                        )
                    }
                };

                if concrete_path.is_file() {
                    process_and_copy(
                        &concrete_path,
                        &target_path,
                        &copy_config.replace,
                        config,
                        &gpm_processor,
                        self.should_process_with_gpm(&concrete_path),
                    )?;
                } else if concrete_path.is_dir() {
                    copy_directory(
                        &concrete_path,
                        &target_path,
                        &copy_config.replace,
                        config,
                        &gpm_processor,
                        &|p| self.should_process_with_gpm(p),
                    )?;
                }
                continue;
            }

            // Handle glob patterns
            if has_wildcards {
                // Create the full pattern for globbing
                let full_pattern = if pattern_str.starts_with('/') {
                    format!("{}{}", search_base.display(), pattern_str)
                } else {
                    format!("{}/{}", search_base.display(), pattern_str)
                };

                log::debug!("Using glob pattern: {}", full_pattern);

                let glob = globset::GlobBuilder::new(&full_pattern)
                    .case_insensitive(false)
                    .literal_separator(false)
                    .build()?
                    .compile_matcher();

                // Walk through source directory
                let mut found_matches = false;
                for entry in walkdir::WalkDir::new(&search_base) {
                    let entry = entry?;
                    let path = entry.path();

                    if path.is_file() || path.is_dir() {
                        let path_str = path.to_string_lossy();

                        if glob.is_match(&*path_str) {
                            found_matches = true;

                            // Get relative path for creating target path
                            let relative_path = path.strip_prefix(&search_base)?;

                            // Determine target path
                            let target_path = if let Some(dest) = &copy_config.destination {
                                if copy_config.flatten {
                                    if path.is_file() {
                                        target_base.join(dest).join(
                                            path.file_name().ok_or_else(|| {
                                                anyhow::anyhow!("Invalid file name")
                                            })?,
                                        )
                                    } else {
                                        target_base.join(dest).join(path.file_name().ok_or_else(
                                            || anyhow::anyhow!("Invalid directory name"),
                                        )?)
                                    }
                                } else {
                                    target_base.join(dest).join(relative_path)
                                }
                            } else {
                                target_base.join(relative_path)
                            };

                            if path.is_file() {
                                process_and_copy(
                                    path,
                                    &target_path,
                                    &copy_config.replace,
                                    config,
                                    &gpm_processor,
                                    self.should_process_with_gpm(path),
                                )?;
                            } else if path.is_dir() {
                                copy_directory(
                                    path,
                                    &target_path,
                                    &copy_config.replace,
                                    config,
                                    &gpm_processor,
                                    &|p| self.should_process_with_gpm(p),
                                )?;
                            }
                        }
                    }
                }

                if !found_matches {
                    log::warn!(
                        "No files or directories matched pattern: {} (searched in {})",
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
