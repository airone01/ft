//! Test execution framework
//!
//! Provides:
//! - TestCase: Structure representing a single test
//! - TestRunner: Trait for implementing test execution
//! - TestResult/TestStatus: Test execution outcomes
//!
use std::{fmt, process, time::Duration};

use async_trait::async_trait;
use log::error;

use crate::runner::{c::CTestRunner, results::TestResults};

pub mod c;
pub mod cat_e;
pub mod results;

#[derive(Debug, Clone)]
pub struct TestCase {
    pub name: String,
    pub source: String,
    pub test_inputs: Vec<TestInput>,
}

#[derive(Debug, Clone)]
pub struct TestInput {
    pub input: String,
    pub expected: String,
    pub index: usize,
}

#[async_trait]
pub trait TestLoader {
    async fn load_tests(&mut self) -> std::io::Result<()>;
    fn get_test_cases(&self) -> Vec<TestCase>;
}

pub async fn run_project_tests<T: TestLoader>(
    mut test_loader: T,
    runner: CTestRunner,
) -> TestResults {
    // Load tests
    if let Err(e) = test_loader.load_tests().await {
        error!("Error loading tests: {}", e);
        process::exit(1);
    }

    let test_cases = test_loader.get_test_cases();
    let mut test_results = TestResults::default();
    let mut handles = vec![];

    // Spawn test tasks
    for test in test_cases {
        let runner_clone = runner.clone();
        let handle = tokio::spawn(async move {
            let result = runner_clone.run(&test).await;
            (test.name.clone(), result)
        });
        handles.push(handle);
    }

    // Wait for all tests to complete
    for handle in handles {
        if let Ok((name, result)) = handle.await {
            test_results.add_function_result(name, result);
        }
    }

    test_results
}

impl TestCase {
    pub fn new(name: String, source: String, inputs: Vec<(String, String)>) -> Self {
        let test_inputs = inputs
            .into_iter()
            .enumerate()
            .map(|(i, (input, expected))| TestInput {
                input,
                expected,
                index: i + 1,
            })
            .collect();

        Self {
            name,
            source,
            test_inputs,
        }
    }
}

#[derive(Debug, Clone)]
pub enum TestError {
    Compilation(String),
    Runtime(String),
    FileSystem(String),
    Other(String),
}

impl fmt::Display for TestError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            TestError::Compilation(msg) => write!(f, "Compilation Error: {}", msg),
            TestError::Runtime(msg) => write!(f, "Runtime Error: {}", msg),
            TestError::FileSystem(msg) => write!(f, "File System Error: {}", msg),
            TestError::Other(msg) => write!(f, "Error: {}", msg),
        }
    }
}

#[derive(Debug, Clone)]
pub enum TestStatus {
    Passed,
    Failed(TestError),
}

impl fmt::Display for TestStatus {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            TestStatus::Passed => write!(f, "Passed"),
            TestStatus::Failed(err) => write!(f, "{}", err),
        }
    }
}

#[derive(Clone, Debug)]
pub struct IndividualResult {
    pub input: String,
    pub expected: String,
    pub actual: String,
    pub passed: bool,
    pub index: usize,
}

#[derive(Clone)]
pub struct TestResult {
    pub status: TestStatus,
    pub duration: Duration,
    pub results: Vec<IndividualResult>,
}

#[async_trait]
pub trait TestRunner {
    async fn run(&self, test_case: &TestCase) -> TestResult;
}
