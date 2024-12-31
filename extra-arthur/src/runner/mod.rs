//! Test execution framework
//!
//! Provides:
//! - TestCase: Structure representing a single test
//! - TestRunner: Trait for implementing test execution
//! - TestResult/TestStatus: Test execution outcomes
//!
use std::fmt;
use std::time::Duration;
pub mod c;

#[derive(Debug, Clone)]
pub struct TestCase {
    pub id: usize,
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

impl TestCase {
    pub fn new(id: usize, name: String, source: String, inputs: Vec<(String, String)>) -> Self {
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
            id,
            name,
            source,
            test_inputs,
        }
    }
}

#[derive(Debug, Clone)]
pub enum TestStatus {
    NotStarted,
    Compiling,
    Running,
    Passed,
    Failed(String),
}

#[derive(Debug)]
pub struct IndividualResult {
    pub input: String,
    pub expected: String,
    pub actual: String,
    pub passed: bool,
    pub index: usize,
}

impl fmt::Display for TestStatus {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            TestStatus::NotStarted => write!(f, "Not Started"),
            TestStatus::Compiling => write!(f, "Compiling"),
            TestStatus::Running => write!(f, "Running"),
            TestStatus::Passed => write!(f, "Passed"),
            TestStatus::Failed(err) => write!(f, "Failed: {}", err),
        }
    }
}

pub struct TestResult {
    pub status: TestStatus,
    pub duration: Duration,
    pub results: Vec<IndividualResult>,
}

pub trait TestRunner {
    fn run(&self, test_case: &TestCase) -> TestResult;
    fn cleanup(&self) -> std::io::Result<()>;
}
