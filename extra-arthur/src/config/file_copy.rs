use serde::{Deserialize, Serialize};

use super::text_replacement::TextReplacement;

#[derive(Debug, Serialize, Deserialize)]
pub struct FileCopyConfig {
    /// Source file or glob pattern
    pub source: String,
    /// Optional destination path (relative to project root)
    /// If not specified, maintains same path structure as source
    pub destination: Option<String>,
    /// Whether to flatten directory structure when copying
    #[serde(default)]
    pub flatten: bool,
    /// Text replacements to apply during copying
    #[serde(default)]
    pub replace: Vec<TextReplacement>,
}
