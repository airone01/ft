use std::process;

use clap::Parser;
use log::{debug, error, info};
use tokio;

use crate::{
    cli::Args,
    projects::{LibftTest, Project},
    runner::{c::CTestRunner, results::TestResults, TestRunner},
};

mod cli;
mod projects;
mod runner;

#[tokio::main]
async fn main() {
    pretty_env_logger::init();

    let args = Args::parse();
    info!("Starting test runner in directory: {}", args.cwd.display());

    // Detect project type
    let project = Project::detect(&args.cwd);
    debug!("Project detection result: {:?}", project);

    // Early exit if project type is unknown
    if matches!(project, Project::Unknown) {
        error!("No supported project detected in the current directory");
        process::exit(1);
    }

    // Load test cases for the project
    match project {
        Project::Libft => {
            let runner = CTestRunner::new(args.cwd.clone(), "ft".to_string());
            let mut libft = LibftTest::new();

            if let Err(e) = libft.load_tests().await {
                error!("Error loading tests: {}", e);
                process::exit(1);
            }

            let test_cases = libft.get_test_cases();
            let mut test_results = TestResults::default();
            let mut handles = vec![];

            for test in test_cases {
                let runner_clone = runner.clone(); // Need to implement Clone
                let handle = tokio::spawn(async move {
                    let result = runner_clone.run(&test).await;
                    (test.name.clone(), result)
                });
                handles.push(handle);
            }

            // Wait for all tests to complete
            for handle in handles {
                if let Ok((name, result)) = handle.await {
                    // Store the result
                    test_results.add_function_result(name, result);
                }
            }

            test_results.display_summary();
        }
        Project::Unknown => unreachable!(),
    }
}
