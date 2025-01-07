use std::path::PathBuf;
use log::debug;
use crate::runner::{TestCase};

pub struct GetNextLineTest {
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

impl GetNextLineTest {
    pub fn new() -> Self {
        Self { test_files: vec![] }
    }

    pub async fn load_tests(&mut self) -> std::io::Result<()> {
        // Load test file
        let test_dir = PathBuf::from("tests/get_next_line");
        debug!("Loading GNL tests from: {}", test_dir.display());

        let test_path = test_dir.join("test.c");
        let inputs_path = test_dir.join("inputs.txt");

        if test_path.exists() && inputs_path.exists() {
            debug!("Loading test files for get_next_line");
            let source = std::fs::read_to_string(test_path)?;
            let inputs = std::fs::read_to_string(inputs_path)?;

            // Parse inputs file - format: input|expected
            let test_cases: Vec<TestInput> = inputs
                .lines()
                .filter(|line| !line.starts_with('#') && !line.is_empty())
                .filter_map(|line| {
                    let parts: Vec<_> = line.split('|').collect();
                    if parts.len() == 2 {
                        Some(TestInput {
                            input: parts[0].to_string(),
                            expected: parts[1].to_string(),
                        })
                    } else {
                        debug!("Invalid test case line: {}", line);
                        None
                    }
                })
                .collect();

            let cases_count = test_cases.len();
            self.test_files.push(TestFile {
                name: "get_next_line".to_string(),
                source,
                test_cases,
            });
            debug!("Loaded {} test cases", cases_count);
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
