use anyhow::Ok;
use clap::Parser as _;
use colored::*;
use env_logger::Env;
use log::info;
use tokio;

use arthur::{
    cli::{Cli, Commands, ProjectCommands},
    commands::{list::List, submit::Submit},
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
            ProjectCommands::List { project_name } => {
                List::new(&project_name, cli.cwd).execute()?;
            }
        }
    }

    Ok(())
}
