use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::path::{Path, PathBuf};

pub(crate) mod push;

#[derive(Debug, Serialize, Deserialize)]
pub struct Config {
    project_paths: HashMap<String, PathBuf>,
}

impl Config {
    pub fn load() -> anyhow::Result<Self> {
        // Load from config file or use defaults
        Ok(Self {
            project_paths: HashMap::from([
                ("libft".to_string(), "milestone-0-libft".into()),
                (
                    "get_next_line".to_string(),
                    "milestone-1-get_next_line".into(),
                ),
                ("ft_printf".to_string(), "milestone-1-ft_printf".into()),
                ("push_swap".to_string(), "milestone-2-push_swap".into()),
            ]),
        })
    }

    pub fn get_project_path(&self, project_name: &str) -> Option<&Path> {
        self.project_paths.get(project_name).map(|p| p.as_path())
    }
}
