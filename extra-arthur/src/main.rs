use std::process;

use anyhow::Ok;
use clap::Parser as _;
use colored::*;
use env_logger::Env;
use log::{debug, error, info};
use tokio;

use arthur::{
    cli::{Cli, Commands, ProjectCommands},
    commands::{submit::Submit, test::Test},
    projects::{LibftTest, Project},
    runner::{c::CTestRunner, results::TestResults, TestRunner},
    Command as _,
};

fn setup_logging(verbose: u8) {
    let env = Env::default().filter_or(
        "GPM_LOG",
        match verbose {
            0 => "warn",
            1 => "info",
            2 => "debug",
            _ => "trace",
        },
    );

    env_logger::Builder::from_env(env)
        .format(|buf, record| {
            use std::io::Write;
            let level_color = match record.level() {
                log::Level::Error => "red",
                log::Level::Warn => "yellow",
                log::Level::Info => "green",
                log::Level::Debug => "blue",
                log::Level::Trace => "magenta",
            };
            writeln!(
                buf,
                "{}: {}",
                record.level().to_string().color(level_color),
                record.args()
            )
        })
        .init();
}

#[tokio::main]
async fn main() -> anyhow::Result<()> {
    let cli = Cli::parse();
    setup_logging(cli.verbose);

    // Use the parsed arguments
    match cli.command {
        Commands::Project { command } => match command {
            ProjectCommands::Submit {
                project_name,
                target_repo,
            } => {
                info!("Submitting project {}", target_repo);
                Submit::new(&project_name, &target_repo).execute()?;
            }
            ProjectCommands::Doctor { project_name } => {
                println!("Running doctor on project {}", project_name);
            }
            ProjectCommands::Test { project_name } => {
                println!("Testing project at {}", project_name);
                Test::new(&project_name).execute()?;
            }
        },
        Commands::Test => {
            // Detect project type
            let project = Project::detect(&cli.cwd);
            debug!("Project detection result: {:?}", project);

            // Early exit if project type is unknown
            if matches!(project, Project::Unknown) {
                error!("No supported project detected in the current directory");
                process::exit(1);
            }

            // Load test cases for the project
            match project {
                Project::Libft => {
                    let runner = CTestRunner::new(cli.cwd.clone(), "ft".to_string());
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
                        if let std::result::Result::Ok((name, result)) = handle.await {
                            // Store the result
                            test_results.add_function_result(name, result);
                        }
                    }

                    test_results.display_summary();
                }
                Project::Unknown => unreachable!(),
            }
        }
    }

    Ok(())
}
