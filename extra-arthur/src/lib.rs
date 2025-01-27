pub mod cli;
pub mod commands;
pub mod config;
pub mod error;
pub mod git;
pub mod processor;
pub mod projects;
pub mod runner;
pub mod validation;

pub trait Command {
    fn execute(&mut self) -> anyhow::Result<()>;
}
