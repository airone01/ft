use crate::error::GpmError;
use anyhow::Context;
use globset::{Glob, GlobSet, GlobSetBuilder};
use serde::{Deserialize, Serialize};
use std::path::{Path, PathBuf};

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

#[derive(Debug, Serialize, Deserialize)]
pub struct SubmitConfig {
    pub files: Vec<String>,
    pub exclude: Option<Vec<String>>,
    pub preprocessor: PreprocessorConfig,
    #[serde(default)]
    pub hooks: HooksConfig,
    #[serde(default)]
    pub validation: ValidationConfig,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct PreprocessorConfig {
    pub enable_gpm: bool,
    pub function_paths: Vec<PathBuf>,
}

#[derive(Debug, Serialize, Deserialize, Default)]
pub struct HooksConfig {
    pub pre_submit: Option<String>,
    pub post_submit: Option<String>,
}

#[derive(Debug, Serialize, Deserialize, Default)]
pub struct ValidationConfig {
    #[serde(default)]
    pub norminette: bool,
    #[serde(default)]
    pub make_test: bool,
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

        self.validate_config(&config)?;

        Ok(config)
    }

    fn validate_config(&self, config: &PushConfiguration) -> anyhow::Result<()> {
        // Validate file patterns
        if config.submit.files.is_empty() {
            return Err(GpmError::ConfigError("No files specified in push.toml".into()).into());
        }

        // Validate function paths if GPM is enabled
        if config.submit.preprocessor.enable_gpm {
            for path in &config.submit.preprocessor.function_paths {
                if !path.exists() {
                    return Err(GpmError::ConfigError(format!(
                        "Function path not found: {}",
                        path.display()
                    ))
                    .into());
                }
            }
        }

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

    fn matches_pattern(path: &Path, pattern: &str) -> bool {
        // Simple glob pattern matching
        // In a real implementation, you might want to use the 'glob' crate
        let path_str = path.to_string_lossy();
        if pattern.contains("*") {
            let parts: Vec<&str> = pattern.split('*').collect();
            let mut current_pos = 0;

            for part in parts {
                if let Some(pos) = path_str[current_pos..].find(part) {
                    current_pos += pos + part.len();
                } else {
                    return false;
                }
            }
            true
        } else {
            path_str == pattern
        }
    }

    fn build_glob_set(patterns: &[String]) -> anyhow::Result<GlobSet> {
        let mut builder = GlobSetBuilder::new();
        for pattern in patterns {
            builder.add(Glob::new(pattern)?);
        }
        Ok(builder.build()?)
    }
}

impl PreprocessorConfig {
    pub fn validate(&self) -> anyhow::Result<()> {
        if self.enable_gpm {
            // Validate function paths
            if self.function_paths.is_empty() {
                return Err(GpmError::ConfigError(
                    "No function paths specified while GPM is enabled".into(),
                )
                .into());
            }

            // Check if paths exist
            for path in &self.function_paths {
                if !path.exists() {
                    return Err(GpmError::ConfigError(format!(
                        "Function path does not exist: {}",
                        path.display()
                    ))
                    .into());
                }
            }
        }

        Ok(())
    }
}

impl PushConfiguration {
    pub fn validate(&self) -> anyhow::Result<()> {
        // Validate project info
        if self.project.name.is_empty() {
            return Err(GpmError::ConfigError("Project name cannot be empty".into()).into());
        }

        // Validate submit config
        if self.submit.files.is_empty() {
            return Err(GpmError::ConfigError("No files specified for submission".into()).into());
        }

        // Validate glob patterns
        for pattern in &self.submit.files {
            if let Err(e) = globset::Glob::new(pattern) {
                return Err(GpmError::InvalidGlobPattern(format!(
                    "Invalid include pattern '{}': {}",
                    pattern, e
                ))
                .into());
            }
        }

        if let Some(excludes) = &self.submit.exclude {
            for pattern in excludes {
                if let Err(e) = globset::Glob::new(pattern) {
                    return Err(GpmError::InvalidGlobPattern(format!(
                        "Invalid exclude pattern '{}': {}",
                        pattern, e
                    ))
                    .into());
                }
            }
        }

        // Validate preprocessor config
        self.submit.preprocessor.validate()?;

        Ok(())
    }
}
