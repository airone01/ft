use std::path::Path;

pub trait GitOperations {
    fn init_repo(&self, path: &Path) -> anyhow::Result<()>;
    fn commit_changes(&self, message: &str) -> anyhow::Result<()>;
    fn push_to_remote(&self, remote_url: &str, force: bool) -> anyhow::Result<()>;
}
