use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, Default)]
pub struct TextReplacement {
    /// Text to find
    pub find: String,
    /// Text to replace with
    pub replace_with: String,
}
