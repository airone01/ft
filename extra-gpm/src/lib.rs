pub mod commands;
pub mod config;
pub mod error;
pub(crate) mod git;
pub(crate) mod processor;
pub(crate) mod validation;

pub trait Command {
    fn execute(&mut self) -> anyhow::Result<()>;
}
