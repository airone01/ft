use clap::Parser;
use log::{debug, error, info, warn};
use std::process;

use crate::{
    cli::Args,
    projects::{LibftTest, Project},
    runner::{c::CTestRunner, TestRunner},
};

mod cli;
mod projects;
mod runner;

fn main() {
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
            info!("Detected libft project, initializing tests...");

            // Initialize test runner and test cases
            let runner = CTestRunner::new(args.cwd.clone(), "ft".to_string());
            let mut libft = LibftTest::new(args.cwd);

            if let Err(e) = libft.load_tests() {
                error!("Error loading tests: {}", e);
                process::exit(1);
            }

            let test_cases = libft.get_test_cases();
            debug!("Loaded {} test cases", test_cases.len());

            // Run tests
            for test in test_cases {
                debug!("Running test: {}", test.name);
                let result = runner.run(&test);
                match result.status {
                    runner::TestStatus::Passed => {
                        info!(target: &test.name, "✅ Passed ({:?})", result.duration);
                    }
                    runner::TestStatus::Failed(err) => {
                        error!(target: &test.name, "❌ Failed: {}", err);
                        if let Some(output) = result.output {
                            debug!("Test output:\n{}", output);
                        }
                    }
                    _ => warn!(
                        target: &test.name,
                        "❌ Ended with unexpected status: {:?}",
                        result.status
                    ),
                }
            }
        }
        Project::Unknown => unreachable!(),
    }
}