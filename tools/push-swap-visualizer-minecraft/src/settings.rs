use std::path::PathBuf;
use std::process::Command;

use once_cell::sync::OnceCell;

use crate::cli::Args;

#[derive(Debug)]
pub struct Settings {
    pub executable: PathBuf,
    pub makefile: PathBuf,
    pub array_size: i32,
    pub instr_delay: f64,
    pub max_height: i32,
    pub info: bool,
}

impl Default for Settings {
    fn default() -> Self {
        Self {
            executable: PathBuf::from("push_swap"),
            makefile: PathBuf::new(),
            array_size: 100,
            instr_delay: 0.05,
            max_height: 100,
            info: false,
        }
    }
}

static SETTINGS: OnceCell<Settings> = OnceCell::new();

pub fn init_settings(args: &Args) {
    let cwd = PathBuf::from(&args.cwd);

    SETTINGS
        .set(Settings {
            executable: cwd.join(&args.executable),
            makefile: cwd.join(&args.makefile),
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

    if settings.makefile.exists() {
        println!("Launching make...");
        let makefile_dir = settings.makefile.parent().ok_or("Invalid Makefile path")?;
        let makefile_name = settings
            .makefile
            .file_name()
            .ok_or("Invalid Makefile name")?
            .to_str()
            .ok_or("Invalid UTF-8 in Makefile path")?;

        let status = Command::new("make")
            .args(&[
                "--directory",
                makefile_dir
                    .to_str()
                    .ok_or("Invalid UTF-8 in Makefile directory")?,
                "--makefile",
                makefile_name,
            ])
            .current_dir(makefile_dir)
            .status()
            .map_err(|e| format!("Failed to execute make: {}", e))?;

        if !status.success() {
            return Err("Make command failed".into());
        }
        println!("Make complete");
    } else {
        println!("warn: no Makefile found");
    }

    if !settings.executable.exists() {
        return Err(format!(
            "Executable not found at {}\nConsider passing argument -e or running inside a Make project",
            settings.executable.display()
        ));
    }

    Ok(())
}

#[cfg(test)]
mod settings_tests {
    use crate::{get_settings, utils::initialize_test};
    use std::path::PathBuf;

    #[test]
    fn test_settings_init() {
        initialize_test();

        let settings = get_settings();

        assert_eq!(settings.executable, PathBuf::from("/test/path/test_exec"));
        assert_eq!(settings.makefile, PathBuf::from("/test/path/test_make"));
        assert_eq!(settings.array_size, 50);
        assert_eq!(settings.instr_delay, 0.1);
        assert_eq!(settings.max_height, 75);
        assert!(settings.info);
    }
}
