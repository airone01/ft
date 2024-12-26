use std::path::PathBuf;
use std::process::Command;

use once_cell::sync::OnceCell;

use crate::cli::Args;

#[derive(Debug)]
pub struct Settings {
    pub executable: String,
    pub cwd: String,
    pub makefile: String,
    pub array_size: i32,
    pub instr_delay: f64,
    pub max_height: i32,
    pub info: bool,
}

impl Default for Settings {
    fn default() -> Self {
        Self {
            executable: String::from("push_swap"),
            cwd: String::from("."),
            makefile: String::new(),
            array_size: 100,
            instr_delay: 0.05,
            max_height: 100,
            info: false,
        }
    }
}

static SETTINGS: OnceCell<Settings> = OnceCell::new();

pub fn init_settings(args: &Args) {
    SETTINGS
        .set(Settings {
            executable: args.executable.clone(),
            cwd: args.cwd.clone(),
            makefile: args.makefile.clone(),
            array_size: args.array_size,
            instr_delay: args.instr_delay,
            max_height: args.max_height,
            info: args.info,
        })
        .unwrap();
}

pub fn get_settings() -> &'static Settings {
    SETTINGS.get().unwrap()
}

pub fn setup_executable() -> Result<(), String> {
    let settings = get_settings();
    let cwd = PathBuf::from(&settings.cwd);

    // Check for Makefile
    let makefile_path = if settings.makefile.starts_with('/') {
        PathBuf::from(&settings.makefile)
    } else {
        cwd.join(&settings.makefile)
    };

    if makefile_path.exists() {
        println!("Launching make...");
        let status = Command::new("make")
            .args(&[
                "--directory",
                makefile_path.parent().unwrap().to_str().unwrap(),
                "--makefile",
                makefile_path.file_name().unwrap().to_str().unwrap(),
            ])
            .current_dir(makefile_path.parent().unwrap())
            .status()
            .map_err(|e| format!("Failed to execute make: {}", e))?;

        if !status.success() {
            return Err("Make command failed".into());
        }
        println!("Make complete");
    } else {
        println!("Warning: no Makefile found");
    }

    // Check executable
    let exec_path = if settings.executable.starts_with('/') {
        PathBuf::from(&settings.executable)
    } else {
        cwd.join(&settings.executable)
    };

    if !exec_path.exists() {
        return Err(format!("Executable not found at {}\nConsider passing argument -e or running inside a Make project", exec_path.display()));
    }

    Ok(())
}

#[cfg(test)]
mod settings_tests {
    use crate::{get_settings, utils::initialize_test};

    #[test]
    fn test_settings_init() {
        initialize_test();

        let settings = get_settings();

        assert_eq!(settings.executable, "test_exec");
        assert_eq!(settings.makefile, "test_make");
        assert_eq!(settings.array_size, 50);
        assert_eq!(settings.instr_delay, 0.1);
        assert_eq!(settings.max_height, 75);
        assert!(settings.info);
    }
}
