<img src="https://skillicons.dev/icons?i=rust" align="right" />

# Arthur - 42 Project Tester

A test runner for 42 school projects. Currently supports:

- libft

## Project Structure

```
src/
  projects/       # Project-specific test configurations
    *.rs          # Project test implementation
    mod.rs        # Project detection and common traits
  runner/         # Test execution engine
    c.rs          # C-specific test runner
    mod.rs        # Core test runner traits and types
  cli.rs          # Command-line interface
  main.rs         # Application entry point
tests/
  */              # Project test cases
    */            # Each function has its own directory
      test.c      # Test implementation
      inputs.txt  # Test inputs and expected outputs
```

## Test File Format

Each function test directory should contain:

- `test.c`: Test implementation that accepts arguments and produces output
- `inputs.txt`: Test cases in the format `input|expected_output`, one per line
    - Lines starting with # are treated as comments
    - Empty lines are ignored

## Adding New Tests

1. Create a directory under `tests/libft/` with your function name
2. Add `test.c` and `inputs.txt`
3. Test files will be automatically detected and run

## Running Tests

Set log level for different output detail:

```bash
RUST_LOG=info cargo run  # Normal output
RUST_LOG=debug cargo run # Detailed debug info
```