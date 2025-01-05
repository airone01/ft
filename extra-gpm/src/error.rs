use std::path::PathBuf;
use thiserror::Error;

#[derive(Error, Debug)]
pub enum GpmError {
    #[error("File not found: {0}")]
    FileNotFound(PathBuf),

    #[error("IO error: {0}")]
    IoError(#[from] std::io::Error),

    #[error("Configuration error: {0}")]
    ConfigError(String),

    #[error("Processing error: {0}")]
    ProcessingError(String),

    #[error("Function {name} not found in {path}")]
    FunctionNotFound { name: String, path: PathBuf },

    #[error("Malformed function markers in {path}")]
    MalformedFunctionMarkers { path: PathBuf },

    #[error("Invalid glob pattern: {0}")]
    InvalidGlobPattern(String),

    #[error("Hook execution failed: {command} ({status})")]
    HookFailed {
        command: String,
        status: std::process::ExitStatus,
    },
}
