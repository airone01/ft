use std::fmt;
use std::time::Duration;
pub mod c;

#[derive(Debug, Clone)]
pub struct TestCase {
    pub id: usize,
    pub name: String,
    pub source: String,
    pub args: Vec<String>,
    pub expected_outputs: Vec<String>,
}

impl TestCase {
    pub fn new(id: usize, name: String, source: String, args: Vec<String>) -> Self {
        Self {
            id,
            name,
            source,
            args,
            expected_outputs: Vec::new(),
        }
    }

    pub fn with_expected_outputs(mut self, outputs: Vec<String>) -> Self {
        self.expected_outputs = outputs;
        self
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
    pub output: Option<String>,
}

pub trait TestRunner {
    fn run(&self, test_case: &TestCase) -> TestResult;
    fn cleanup(&self) -> std::io::Result<()>;
}
