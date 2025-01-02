use std::process::Command;

use log::*;

use crate::get_settings;

pub async fn execute_push_swap(numbers: &[i32]) -> Result<String, String> {
    // Create command with path from settings
    let mut cmd = Command::new(get_settings().executable.clone());

    // Add each number as a separate argument
    for num in numbers {
        cmd.arg(num.to_string());
    }

    // Execute the command
    debug!("Executing push_swap with {} numbers", numbers.len());
    let output = cmd
        .output()
        .map_err(|e| format!("Failed to execute push_swap: {}", e))?;
    debug!("push_swap executed with status: {}", output.status);

    // Check if the execution was successful
    if output.status.success() {
        // Convert output bytes to string
        String::from_utf8(output.stdout)
            .map_err(|e| format!("Failed to parse push_swap output: {}", e))
    } else {
        // Return error message if execution failed
        let error = String::from_utf8_lossy(&output.stderr);
        Err(format!("push_swap failed: {}", error))
    }
}
