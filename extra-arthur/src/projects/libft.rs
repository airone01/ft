use async_trait::async_trait;
use std::path::PathBuf;

use log::debug;

use crate::runner::{cat_e::CatE, TestCase, TestLoader};

pub struct LibFtTest {
    test_files: Vec<TestFile>,
}

struct TestFile {
    name: String,
    source: String,
    test_cases: Vec<TestInput>,
}

struct TestInput {
    input: String,
    expected: String,
}

#[async_trait]
impl TestLoader for LibFtTest {
    async fn load_tests(&mut self) -> std::io::Result<()> {
        // Existing load_tests implementation
        self.load_tests().await
    }

    fn get_test_cases(&self) -> Vec<TestCase> {
        // Existing get_test_cases implementation
        self.get_test_cases()
    }
}

impl LibFtTest {
    pub fn new() -> Self {
        Self { test_files: vec![] }
    }

    pub async fn load_tests(&mut self) -> std::io::Result<()> {
        // Load all test directories under tests/libft/
        let test_dir = PathBuf::from("tests/libft");
        debug!("Looking for tests in: {}", test_dir.display());

        let mut entries = tokio::fs::read_dir(&test_dir).await?;
        while let Some(entry) = entries.next_entry().await? {
            let entry = entry;
            if entry.file_type().await?.is_dir() {
                let fn_name = entry.file_name();
                let fn_name = fn_name.to_string_lossy();
                debug!("Found test directory: {}", fn_name);

                // Each function directory should have:
                // - test.c (the test implementation)
                // - inputs.txt (list of test inputs and expected outputs)
                let test_path = entry.path().join("test.c");
                let inputs_path = entry.path().join("inputs.txt");

                if test_path.exists() && inputs_path.exists() {
                    debug!("Loading test files for {}", fn_name);
                    let source = std::fs::read_to_string(test_path)?;
                    let inputs = std::fs::read_to_string(inputs_path)?;

                    // Parse inputs file - format: input|expected
                    let test_cases: Vec<TestInput> = inputs
                        .lines()
                        .filter(|line| !line.starts_with('#') && !line.is_empty())
                        .filter_map(|line| {
                            let parts: Vec<_> = line.split('|').collect();
                            if parts.len() == 2 {
                                let input = parts[0].to_string();
                                let expected = parts[1]
                                    .replace("\\n", "\n")
                                    .replace("\\t", "\t")
                                    .replace("\\v", "\u{000b}")
                                    .replace("\\r", "\r")
                                    .replace("\\f", "\u{000c}");
                                debug!(
                                    "Testing input: {:<10} expecting: {}",
                                    input.debug_display(),
                                    expected.debug_display()
                                );
                                Some(TestInput { input, expected })
                            } else {
                                debug!("Invalid test case line: {}", line);
                                None
                            }
                        })
                        .collect();

                    let cases_count = test_cases.len();
                    self.test_files.push(TestFile {
                        name: fn_name.to_string(),
                        source,
                        test_cases,
                    });
                    debug!("Loaded {} test cases for {}", cases_count, fn_name);
                } else {
                    debug!("Missing test files for {}", fn_name);
                }
            }
        }
        Ok(())
    }

    pub fn get_test_cases(&self) -> Vec<TestCase> {
        self.test_files
            .iter()
            .map(|test| {
                let inputs = test
                    .test_cases
                    .iter()
                    .map(|tc| (tc.input.clone(), tc.expected.clone()))
                    .collect::<Vec<_>>();

                TestCase::new(test.name.clone(), test.source.clone(), inputs)
            })
            .collect()
    }
}
