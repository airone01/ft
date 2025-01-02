use clap::Parser;
use std::path::PathBuf;

/// A tester for 42 exercises
#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
pub struct Args {
    // Options/flags
    /// What to test (optional)
    #[arg(short, long)]
    name: Option<String>,

    // Environment variables
    /// Current working directory
    #[arg(long, env, default_value = ".")]
    pub(crate) cwd: PathBuf,
}
