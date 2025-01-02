//! Project detection and configuration
//!
//! This module handles:
//! - Detecting project type from directory contents
//! - Loading appropriate test configurations
//! - Managing project-specific settings

use log::{debug, info};
use std::{fs, path::Path};

pub mod libft;
pub use libft::*;

#[derive(Debug)]
pub enum Project {
    Libft,
    Unknown,
}

impl Project {
    pub fn detect(path: &Path) -> Self {
        debug!("Checking directory: {}", path.display());

        let files = match fs::read_dir(path) {
            Ok(entries) => entries
                .filter_map(Result::ok)
                .map(|e| e.file_name().to_string_lossy().to_string())
                .collect::<Vec<_>>(),
            Err(e) => {
                debug!("Error reading directory: {}", e);
                return Project::Unknown;
            }
        };

        debug!("Found files: {:?}", files);

        // For libft, check if libft.h exists
        if files.iter().any(|f| f == "libft.h") {
            info!("Found libft.h - detected as Libft project");
            return Project::Libft;
        }

        debug!("No project detected");
        Project::Unknown
    }
}
