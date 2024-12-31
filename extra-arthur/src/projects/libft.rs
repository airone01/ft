use crate::runner::TestCase;
use log::{debug, info};
use std::path::PathBuf;

pub struct LibftTest {
    work_dir: PathBuf,
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

impl LibftTest {
    pub fn new(work_dir: PathBuf) -> Self {
        Self {
            work_dir,
            test_files: vec![],
        }
    }

    pub fn load_tests(&mut self) -> std::io::Result<()> {
        // Load all test directories under tests/libft/
        let test_dir = PathBuf::from("tests/libft");
        debug!("Looking for tests in: {}", test_dir.display());

        for entry in std::fs::read_dir(test_dir)? {
            let entry = entry?;
            if entry.file_type()?.is_dir() {
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
                                let expected = parts[1].replace("\\n", "\n");
                                debug!("Test case - Input: {:?}, Expected: {:?}", input, expected);
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
                    info!("Loaded {} test cases for {}", cases_count, fn_name);
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
            .enumerate()
            .map(|(id, test)| {
                TestCase::new(
                    id,
                    test.name.clone(),
                    test.source.clone(),
                    test.test_cases.iter().map(|tc| tc.input.clone()).collect(),
                )
                .with_expected_outputs(
                    test.test_cases
                        .iter()
                        .map(|tc| tc.expected.clone())
                        .collect(),
                )
            })
            .collect()
    }
}
