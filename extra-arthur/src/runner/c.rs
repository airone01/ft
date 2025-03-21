//! C-specific test runner implementation
//!
//! Handles:
//! - Compiling C test files
//! - Linking with project libraries
//! - Running tests and capturing output
//! - Comparing results with expected output

use std::{
    path::{Path, PathBuf},
    time::Instant,
};

use async_trait::async_trait;
use walkdir::WalkDir;

use super::{IndividualResult, TestCase, TestError, TestResult, TestRunner, TestStatus};
#[derive(Clone)]
pub struct CTestRunner {
    work_dir: PathBuf,
    project_type: ProjectType,
}

#[derive(Clone)]
enum ProjectType {
    LibFt,
    GetNextLine,
}

impl CTestRunner {
    pub fn new(work_dir: PathBuf, project_name: &str) -> Self {
        let project_type = match project_name {
            "ft" => ProjectType::LibFt,
            "gnl" => ProjectType::GetNextLine,
            _ => panic!("Unsupported project type"),
        };

        Self {
            work_dir,
            project_type,
        }
    }

    async fn compile(&self, test_file: &Path, output_file: &Path) -> Result<(), TestError> {
        let mut command = tokio::process::Command::new("cc");
        command
            .current_dir(&self.work_dir)
            .args(&["-Wall", "-Wextra", "-Werror", "-g3"])
            .arg("-o")
            .arg(output_file)
            .arg(test_file);

        // Add project-specific compilation flags
        match self.project_type {
            ProjectType::LibFt => {
                command.arg("-L.").arg("-I.").arg("-lft");
            }
            ProjectType::GetNextLine => {
                // Find and compile get_next_line source files
                let mut source_files = vec![];
                for entry in WalkDir::new(&self.work_dir) {
                    let entry = entry.map_err(|e| {
                        TestError::Compilation(format!("Error scanning directory: {}", e))
                    })?;
                    let path = entry.path();
                    if path.is_file() && path.extension().and_then(|s| s.to_str()) == Some("c") {
                        let name = path.file_name().unwrap().to_string_lossy();
                        if name.starts_with("get_next_line") {
                            source_files.push(path.to_path_buf());
                        }
                    }
                }

                // Add source files and include directory
                command.args(&source_files);
                command.arg("-I.").arg("-D").arg("BUFFER_SIZE=42");
            }
        }

        let output = command
            .output()
            .await
            .map_err(|e| TestError::Compilation(format!("Failed to compile: {}", e)))?;

        if !output.status.success() {
            return Err(TestError::Compilation(
                String::from_utf8_lossy(&output.stderr).to_string(),
            ));
        }

        Ok(())
    }

    async fn run_single_test(&self, executable: &Path, arg: &str) -> Result<String, TestError> {
        let output = tokio::process::Command::new(executable)
            .current_dir(&self.work_dir)
            .arg(arg)
            .output()
            .await
            .map_err(|e| TestError::Runtime(format!("Failed to execute test: {}", e)))?;

        if !output.status.success() {
            return Err(TestError::Runtime(
                String::from_utf8_lossy(&output.stderr).to_string(),
            ));
        }

        Ok(String::from_utf8_lossy(&output.stdout).to_string())
    }
}

#[async_trait]
impl TestRunner for CTestRunner {
    async fn run(&self, test_case: &TestCase) -> TestResult {
        let start_time = Instant::now();
        let temp_dir = tempfile::tempdir().unwrap();
        let test_file = temp_dir.path().join(format!("{}.c", test_case.name));
        let output_file = temp_dir.path().join(&test_case.name);

        // Write and compile test file
        if let Err(e) = tokio::fs::write(&test_file, &test_case.source).await {
            return TestResult {
                status: TestStatus::Failed(TestError::FileSystem(format!(
                    "Failed to write test file: {}",
                    e
                ))),
                duration: start_time.elapsed(),
                results: vec![],
            };
        }

        if let Err(err) = self.compile(&test_file, &output_file).await {
            return TestResult {
                status: TestStatus::Failed(err),
                duration: start_time.elapsed(),
                results: vec![],
            };
        }

        // Run individual tests
        let mut results = Vec::new();
        let mut all_passed = true;

        for test_input in &test_case.test_inputs {
            match self.run_single_test(&output_file, &test_input.input).await {
                Ok(output) => {
                    let output = output.trim().to_string();
                    let passed = output == test_input.expected.trim();
                    if !passed {
                        all_passed = false;
                    }

                    results.push(IndividualResult {
                        input: test_input.input.clone(),
                        expected: test_input.expected.clone(),
                        actual: output,
                        passed,
                        index: test_input.index,
                    });
                }
                Err(err) => {
                    return TestResult {
                        status: TestStatus::Failed(err),
                        duration: start_time.elapsed(),
                        results,
                    }
                }
            }
        }

        TestResult {
            status: if all_passed {
                TestStatus::Passed
            } else {
                TestStatus::Failed(TestError::Other("Some tests failed".to_string()))
            },
            duration: start_time.elapsed(),
            results,
        }
    }
}
