//! Project detection and configuration
//!
//! This module handles:
//! - Detecting project type from directory contents
//! - Loading appropriate test configurations
//! - Managing project-specific settings
pub mod libft;
pub mod gnl;

use log::{trace, info, warn};
use std::{fs, path::Path};

pub use libft::*;
pub use gnl::*;

#[derive(Debug)]
pub enum Project {
    Libft,
    GetNextLine,
    Unknown,
}

impl Project {
    pub fn detect(path: &Path) -> Self {
        trace!("Checking directory: {}", path.display());

        let files = match fs::read_dir(path) {
            Ok(entries) => entries
                .filter_map(Result::ok)
                .map(|e| e.file_name().to_string_lossy().to_string())
                .collect::<Vec<_>>(),
            Err(e) => {
                warn!("Error reading directory: {}", e);
                return Project::Unknown;
            }
        };

        trace!("Found files: {:?}", files);

        // For libft, check if libft.h exists
        if files.iter().any(|f| f == "libft.h") {
            info!("Found libft.h - detected as Libft project");
            return Project::Libft;
        }

        // Check for get_next_line first (more specific)
        if files.iter().any(|f| f.contains("get_next_line.h") || f.contains("get_next_line_bonus.h")) {
            info!("Found get_next_line header - detected as Get Next Line project");
            return Project::GetNextLine;
        }

        trace!("No project detected");
        Project::Unknown
    }
}
