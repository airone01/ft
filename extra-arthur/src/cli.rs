use clap::Parser;
use clap::Subcommand;
use std::path::PathBuf;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
pub struct Cli {
    /// Working directory
    #[arg(long, env, default_value = ".", global = true)]
    pub cwd: PathBuf,

    /// Verbose output mode (-v, -vv, -vvv)
    #[arg(short, long, action = clap::ArgAction::Count)]
    pub verbose: u8,

    #[command(subcommand)]
    pub command: Commands,
}

#[derive(Subcommand)]
pub enum Commands {
    /// Project commands
    #[command(alias = "p")]
    Project {
        #[command(subcommand)]
        command: ProjectCommands,
    },

    /// Test commands
    #[command(alias = "t")]
    Test,
}

#[derive(Subcommand)]
pub enum ProjectCommands {
    /// Submit a project
    #[command(alias = "s")]
    Submit {
        /// Name of the project
        project_name: String,

        /// String argument for submission
        target_repo: String,
    },

    /// Run doctor on project
    #[command(alias = "d")]
    Doctor {
        /// Name of the project
        project_name: String,
    },

    /// Test project
    #[command(alias = "t")]
    Test {
        /// Name of the project
        project_name: String,
    },

    /// List all standard functions defined in push config
    #[command(alias = "l")]
    List {
        /// Name of the project
        project_name: String,
    },
}
