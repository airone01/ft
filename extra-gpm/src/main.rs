use clap::{Parser, Subcommand};
use colored::*;
use env_logger::Env;
use gpm::commands::{submit::Submit, test::Test};
use gpm::Command;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Cli {
    #[command(subcommand)]
    command: Commands,

    /// Verbose output mode (-v, -vv, -vvv)
    #[arg(short, long, action = clap::ArgAction::Count)]
    verbose: u8,
}

#[derive(Subcommand)]
enum Commands {
    Submit {
        project_name: String,
        target_repo: String,
    },
    Test {
        project_name: String,
    },
}

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

fn main() -> anyhow::Result<()> {
    let cli = Cli::parse();
    setup_logging(cli.verbose);

    log::info!("Starting GPM...");

    match cli.command {
        Commands::Submit {
            project_name,
            target_repo,
        } => {
            log::info!("📤 Submitting project {}", project_name);
            println!("{}", "📤 Submitting project...".blue());
            Submit::new(&project_name, &target_repo).execute()?;
        }
        Commands::Test { project_name } => {
            log::info!("🧪 Testing project {}", project_name);
            println!("{}", "🧪 Testing submission...".blue());
            Test::new(&project_name).execute()?;
        }
    }

    log::info!("GPM completed successfully");
    Ok(())
}
