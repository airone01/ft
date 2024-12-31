//! C-specific test runner implementation
//!
//! Handles:
//! - Compiling C test files
//! - Linking with project libraries
//! - Running tests and capturing output
//! - Comparing results with expected output

use std::{
    fs,
    path::{Path, PathBuf},
    process::Command,
    time::Instant,
};

use super::{TestCase, TestResult, TestRunner, TestStatus};

pub struct CTestRunner {
    work_dir: PathBuf,
    lib_name: String,
}

impl CTestRunner {
    pub fn new(work_dir: PathBuf, lib_name: String) -> Self {
        Self { work_dir, lib_name }
    }

    fn compile(&self, test_file: &Path, output_file: &Path) -> Result<(), String> {
        let output = Command::new("cc")
            .current_dir(&self.work_dir)
            .arg("-Wall")
            .arg("-Wextra")
            .arg("-Werror")
            .arg("-Wpedantic")
            .arg("-g3")
            .arg("-o")
            .arg(output_file)
            .arg(test_file)
            .arg(format!("-l{}", self.lib_name))
            .arg("-L.") // Add the current directory to library search path
            .arg("-I.") // Add the current directory to header search path
            .output()
            .map_err(|e| format!("Failed to execute gcc: {}", e))?;

        if !output.status.success() {
            return Err(String::from_utf8_lossy(&output.stderr).to_string());
        }

        Ok(())
    }

    fn run_single_test(&self, executable: &Path, arg: &str) -> Result<String, String> {
        let output = Command::new(executable)
            .current_dir(&self.work_dir)
            .arg(arg)
            .output()
            .map_err(|e| format!("Failed to execute test: {}", e))?;

        if !output.status.success() {
            return Err(String::from_utf8_lossy(&output.stderr).to_string());
        }

        Ok(String::from_utf8_lossy(&output.stdout).to_string())
    }
}

impl TestRunner for CTestRunner {
    fn run(&self, test_case: &TestCase) -> TestResult {
        let start_time = Instant::now();
        let temp_dir = tempfile::tempdir().unwrap();
        let test_file = temp_dir.path().join(format!("{}.c", test_case.name));
        let output_file = temp_dir.path().join(&test_case.name);

        // Write test file
        if let Err(e) = fs::write(&test_file, &test_case.source) {
            return TestResult {
                status: TestStatus::Failed(format!("Failed to write test file: {}", e)),
                duration: start_time.elapsed(),
                output: None,
            };
        }

        // Compile
        match self.compile(&test_file, &output_file) {
            Ok(()) => (),
            Err(e) => {
                return TestResult {
                    status: TestStatus::Failed(format!("Compilation failed: {}", e)),
                    duration: start_time.elapsed(),
                    output: None,
                }
            }
        }

        // Run test with each argument and compare outputs
        let mut all_output = String::new();
        for (i, arg) in test_case.args.iter().enumerate() {
            match self.run_single_test(&output_file, arg) {
                Ok(output) => {
                    // Compare with expected output
                    if let Some(expected) = test_case.expected_outputs.get(i) {
                        if output.trim() != expected.trim() {
                            return TestResult {
                                status: TestStatus::Failed(format!(
                                    "Output mismatch for input '{}'\nExpected: {}\nGot: {}",
                                    arg, expected, output
                                )),
                                duration: start_time.elapsed(),
                                output: Some(all_output),
                            };
                        }
                    }
                    all_output.push_str(&output);
                }
                Err(e) => {
                    return TestResult {
                        status: TestStatus::Failed(format!(
                            "Test failed with input '{}': {}",
                            arg, e
                        )),
                        duration: start_time.elapsed(),
                        output: Some(all_output),
                    }
                }
            }
        }

        TestResult {
            status: TestStatus::Passed,
            duration: start_time.elapsed(),
            output: Some(all_output),
        }
    }

    fn cleanup(&self) -> std::io::Result<()> {
        Ok(()) // Temp dir is cleaned up automatically
    }
}
