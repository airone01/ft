use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, Default)]
pub struct HooksConfig {
    pub pre_submit: Option<String>,
    pub temp_prepare: Option<String>,
    pub post_submit: Option<String>,
}
