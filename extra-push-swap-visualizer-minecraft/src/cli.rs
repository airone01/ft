use clap::Parser;

/// A Minecraft server for testing push_swap
#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
pub struct Args {
    /// Push_swap executable path
    #[arg(short, long, default_value = "push_swap")]
    pub executable: String,

    /// Optional Makefile path
    /// If not provided, and the executable is not found in the current working directory, the program will try to build it using the Makefile in the current working directory
    #[arg(short, long, default_value = "Makefile")]
    pub makefile: String,

    /// Display information and settings about the program and exit
    #[arg(short, long, default_value = "false")]
    pub info: bool,

    // --- Environment variables ---
    /// Current working directory
    #[arg(long, env, default_value = ".")]
    pub cwd: String,

    /// Number of numbers to generate
    #[arg(long, env, default_value = "100")]
    pub array_size: i32,

    /// Delay between each instruction
    #[arg(long, env, default_value = "0.05")]
    pub instr_delay: f64,

    /// Maximum length of each number
    #[arg(long, env, default_value = "100", hide = true)]
    pub max_height: i32,
}
