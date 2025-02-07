use std::process;

use anyhow::Ok;
use clap::Parser as _;
use colored::*;
use env_logger::Env;
use log::{debug, error, info};
use tokio;

use arthur::{
    cli::{Cli, Commands, ProjectCommands},
    commands::{list::List, submit::Submit, test::Test},
    projects::{GetNextLineTest, LibFtTest, Project},
    runner::{c::CTestRunner, run_project_tests},
    Command as _,
};

fn setup_logging(verbose: u8) {
    let env = Env::default().filter_or(
        "GPM_LOG",
        match verbose {
            0 => "info",
            1 => "debug",
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
                Submit::new(&project_name, &target_repo, cli.cwd).execute()?;
            }
            ProjectCommands::Doctor { project_name } => {
                println!("Running doctor on project {}", project_name);
            }
            ProjectCommands::Test { project_name } => {
                println!("Testing project at {}", project_name);
                Test::new(cli.cwd, &project_name).execute()?;
            }
            ProjectCommands::List { project_name } => {
                List::new(&project_name, cli.cwd).execute()?;
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
                Project::LibFt => {
                    let runner = CTestRunner::new(cli.cwd.clone(), "ft");
                    let test_results = run_project_tests(LibFtTest::new(), runner).await;
                    test_results.display_summary();
                }
                Project::GetNextLine => {
                    let runner = CTestRunner::new(cli.cwd.clone(), "gnl");
                    let test_results = run_project_tests(GetNextLineTest::new(), runner).await;
                    test_results.display_summary();
                }
                Project::Unknown => unreachable!(),
            }
        }
    }

    Ok(())
}
