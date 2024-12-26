use std::process::Command;

pub async fn execute_push_swap(numbers: &[i32]) -> Result<String, String> {
    // Convert numbers to space-separated string
    let input = numbers
        .iter()
        .map(|n| n.to_string())
        .collect::<Vec<String>>()
        .join(" ");

    // Execute push_swap with the numbers as arguments
    let output = Command::new("./push_swap")
        .arg(&input)
        .output()
        .map_err(|e| format!("Failed to execute push_swap: {}", e))?;

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
