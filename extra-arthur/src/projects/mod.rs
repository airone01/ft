//! Project detection and configuration
//!
//! This module handles:
//! - Detecting project type from directory contents
//! - Loading appropriate test configurations
//! - Managing project-specific settings
pub mod gnl;
pub mod libft;

use log::{info, trace, warn};
use std::{fs, path::Path};

pub use gnl::*;
pub use libft::*;

#[derive(Debug)]
pub enum Project {
    LibFt,
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
            info!("Found libft.h - detected as LibFt project");
            return Project::LibFt;
        }

        // Check for get_next_line first (more specific)
        if files
            .iter()
            .any(|f| f.contains("get_next_line.h") || f.contains("get_next_line_bonus.h"))
        {
            info!("Found get_next_line header - detected as Get Next Line project");
            return Project::GetNextLine;
        }

        trace!("No project detected");
        Project::Unknown
    }
}
