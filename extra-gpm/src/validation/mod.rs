use std::path::Path;
use std::process::Command;

pub struct ValidationManager;

impl ValidationManager {
    pub fn new() -> Self {
        Self
    }

    pub fn check_norminette(&self, path: &Path) -> anyhow::Result<bool> {
        let output = Command::new("norminette").current_dir(path).output()?;

        Ok(output.status.success())
    }

    pub fn run_make_test(&self, path: &Path) -> anyhow::Result<bool> {
        // First run make
        let make_result = Command::new("make").current_dir(path).output()?;

        if !make_result.status.success() {
            return Ok(false);
        }

        // Then run make test
        let test_result = Command::new("make")
            .arg("test")
            .current_dir(path)
            .output()?;

        Ok(test_result.status.success())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::fs;
    use tempfile::TempDir;

    #[test]
    fn test_validation() -> anyhow::Result<()> {
        let temp_dir = TempDir::new()?;
        let validator = ValidationManager::new();

        // Create a mock Makefile
        fs::write(temp_dir.path().join("Makefile"), "test:\n\texit 0\n")?;

        // Test make test execution
        let result = validator.run_make_test(temp_dir.path())?;
        assert!(result);

        Ok(())
    }
}
