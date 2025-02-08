use serde::{Deserialize, Serialize};

use super::{file_copy::FileCopyConfig, hooks::HooksConfig, preprocessor::PreprocessorConfig};

#[derive(Debug, Serialize, Deserialize, Default)]
pub struct ValidationConfig {
    #[serde(default)]
    pub norminette: bool,
    #[serde(default)]
    pub make_test: bool,
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
    #[serde(default)]
    pub copy: Vec<FileCopyConfig>,
}
