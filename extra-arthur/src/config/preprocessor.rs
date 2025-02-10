use std::path::{Path, PathBuf};

use serde::{Deserialize, Serialize};

use crate::error::GpmError;

#[derive(Debug, Serialize, Deserialize)]
pub struct PreprocessorConfig {
    pub enable_gpm: bool,
    pub function_paths: Vec<PathBuf>,
}

impl PreprocessorConfig {
    pub fn validate(&self, project_path: &Path) -> anyhow::Result<()> {
        if self.enable_gpm {
            // Validate function paths
            if self.function_paths.is_empty() {
                return Err(GpmError::ConfigError(
                    "No function paths specified while GPM is enabled".into(),
                )
                .into());
            }

            // Check if paths exist relative to project directory
            for path in &self.function_paths {
                let full_path = project_path.join(path);
                if !full_path.exists() {
                    return Err(GpmError::ConfigError(format!(
                        "Function path does not exist: {}",
                        full_path.display()
                    ))
                    .into());
                }
            }
        }

        Ok(())
    }
}
