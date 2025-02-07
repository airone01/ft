use std::time::Duration;

use crossterm::style::Stylize;
use log::{error, info};

use crate::runner::cat_e::CatE;

use super::{IndividualResult, TestError, TestResult, TestStatus};

#[derive(Default)]
pub struct TestResults {
    total_tests: usize,
    passed_tests: usize,
    compilation_errors: usize,
    runtime_errors: usize,
    function_results: Vec<FunctionResult>,
}

struct FunctionResult {
    name: String,
    status: TestStatus,
    cases: Vec<IndividualResult>,
    duration: Duration,
    total: usize,
    passed: usize,
}

impl TestError {
    fn status_char(&self) -> crossterm::style::StyledContent<&str> {
        match self {
            TestError::Compilation(_) => "C".red().bold(),
            TestError::Runtime(_) => "R".red().bold(),
            TestError::FileSystem(_) => "F".red().bold(),
            TestError::Other(_) => "E (test is probably broken) ".red().bold(),
        }
    }
}

impl TestResults {
    pub fn add_function_result(&mut self, name: String, result: TestResult) {
        match &result.status {
            TestStatus::Failed(TestError::Compilation(_)) => {
                self.compilation_errors += 1;
            }
            TestStatus::Failed(TestError::Runtime(_)) => {
                self.runtime_errors += 1;
            }
            _ => {
                let total = result.results.len();
                let passed = result.results.iter().filter(|r| r.passed).count();
                self.total_tests += total;
                self.passed_tests += passed;
            }
        }

        self.function_results.push(FunctionResult {
            name,
            status: result.status,
            total: result.results.len(),
            cases: result.results.clone(),
            duration: result.duration,
            passed: result.results.iter().filter(|r| r.passed).count(),
        });
    }
    pub fn display_summary(&self) {
        // Display quick summary for each function
        for func in &self.function_results {
            let status_line = match &func.status {
                TestStatus::Failed(err) => err.status_char().to_string(),
                _ => {
                    let mut line = String::new();
                    for case in &func.cases {
                        if case.passed {
                            line.push_str("✔".green().bold().to_string().as_str());
                        } else {
                            line.push_str("X".red().bold().to_string().as_str());
                        }
                    }
                    line
                }
            };

            let result_ratio = match &func.status {
                TestStatus::Failed(TestError::Compilation(_))
                | TestStatus::Failed(TestError::Runtime(_))
                | TestStatus::Failed(TestError::FileSystem(_)) => "0/?".to_string(),
                _ => format!("{}/{}", func.passed, func.total),
            };

            info!("{}\t{:<5} ({:.2?})", func.name, result_ratio, func.duration);
            info!("{}", status_line);
        }

        // Display error messages
        for func in &self.function_results {
            match &func.status {
                TestStatus::Failed(err @ TestError::Compilation(_))
                | TestStatus::Failed(err @ TestError::Runtime(_))
                | TestStatus::Failed(err @ TestError::FileSystem(_)) => {
                    error!("Error in function {}", func.name.clone().yellow());
                    error!("{}", err);
                }
                _ => {
                    for case in &func.cases {
                        if !case.passed {
                            error!(
                                "Error in test number {} of {}",
                                case.index.to_string().yellow(),
                                &func.name.clone().yellow()
                            );
                            error!("Input    : {}", case.input.debug_display());
                            error!("Expected : {}", case.expected.debug_display());
                            error!("Got      : {}", case.actual.debug_display());
                        }
                    }
                }
            }
        }

        // Display overall summary
        info!("");
        info!("{:^26}", "Overall Results".bold());
        info!("Total functions   :{:>7}", self.function_results.len());
        info!("Total test cases  :{:>7}", self.total_tests);
        info!("Passed test cases :{:>7}", self.passed_tests);
        if self.total_tests > 0 {
            info!(
                "Success Rate      :{:>6.0}%",
                (self.passed_tests as f64 / self.total_tests as f64) * 100.0
            );
        }
    }
}
