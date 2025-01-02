use std::process;

use clap::Parser;
use log::{debug, error, info};
use tokio;

use crate::{
    cli::Args,
    projects::{LibftTest, Project},
    runner::{c::CTestRunner, TestRunner},
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
            let mut libft = LibftTest::new(args.cwd);

            if let Err(e) = libft.load_tests().await {
                error!("Error loading tests: {}", e);
                process::exit(1);
            }

            let test_cases = libft.get_test_cases();

            // Run tests concurrently using tokio
            let mut handles = vec![];

            for test in test_cases {
                let runner_clone = runner.clone(); // Need to implement Clone
                let handle = tokio::spawn(async move {
                    let result = runner_clone.run(&test).await;
                    (test.name.clone(), result)
                });
                handles.push(handle);
            }

            let mut passed = 0;
            let mut total = 0;

            // Wait for all tests to complete
            for handle in handles {
                if let Ok((name, result)) = handle.await {
                    info!(target: &name, "  {}:", name);
                    for individual in &result.results {
                        total += 1;

                        if individual.passed {
                            info!(
                                target: &name,
                                "✅ Test {}",
                                individual.index,
                            );
                            passed += 1;
                        } else {
                            info!(
                                target: &name,
                                "❌ Test {}: Input: '{}' -> Expected: '{}', Got: '{}'",
                                individual.index,
                                individual.input,
                                individual.expected,
                                individual.actual
                            );
                        }
                    }

                    let total = result.results.len();
                    let passed = result.results.iter().filter(|r| r.passed).count();
                    info!(
                        target: &name,
                        "Results: {}/{} tests passed ({:?})",
                        passed,
                        total,
                        result.duration
                    );
                }
            }

            info!("Results: {}/{} tests passed", passed, total);
        }
        Project::Unknown => unreachable!(),
    }
}
