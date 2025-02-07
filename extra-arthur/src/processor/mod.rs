use std::path::{Path, PathBuf};

pub(crate) mod function;
pub(crate) mod gpm;

pub trait FileProcessor {
    fn process_file(&self, input: &Path, output: &Path) -> anyhow::Result<()>;
    fn process_directory(&self, input: &Path, output: &Path) -> anyhow::Result<()>;
}

pub trait FunctionExtractor {
    fn find_function(&self, name: &str, search_paths: &[PathBuf])
        -> anyhow::Result<Option<String>>;
    fn extract_function(&self, content: &str, name: &str) -> Option<String>;
}
