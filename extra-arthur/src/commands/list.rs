use crossterm::style::Stylize;
use log::{debug, info};
use prettytable::{format, Cell, Row, Table};
use regex::Regex;
use std::collections::HashMap;
use std::fs;
use std::path::PathBuf;
use walkdir::WalkDir;

use crate::config::push::PushConfigManager;
use crate::Command;

pub struct List {
    project_name: String,
    cwd: PathBuf,
}

/// Represents information about a function in the project
#[derive(Default, Debug)]
struct FunctionInfo {
    /// Whether the function is declared in a header file
    in_header: bool,
    /// Whether the function is implemented in a source file
    in_source: bool,
    /// Whether the function has any GPM directives (GPM@ or GPM!)
    has_gpm_directive: bool,
}

impl List {
    pub fn new(project_name: &str, cwd: PathBuf) -> Self {
        Self {
            project_name: project_name.to_string(),
            cwd,
        }
    }

    /// Scans a single file for function information
    fn scan_file(&self, path: &PathBuf) -> anyhow::Result<HashMap<String, FunctionInfo>> {
        let content = fs::read_to_string(path)?;
        let mut functions: HashMap<String, FunctionInfo> = HashMap::new();

        debug!("Scanning file: {}", path.display());

        // Regular expressions for detecting functions and directives
        let fn_decl =
            Regex::new(r"^\s*(?:static\s+)?[a-zA-Z0-9_]+\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\(")?;
        let gpm_directive = Regex::new(r"(?://|#)\s*GPM[!@]")?;

        // Determine file type
        let is_header = path.extension().and_then(|s| s.to_str()) == Some("h");
        let is_source = path.extension().and_then(|s| s.to_str()) == Some("c");

        // Extract filename without extension (likely the function name in 42 projects)
        let filename = path
            .file_stem()
            .and_then(|s| s.to_str())
            .unwrap_or("")
            .to_string();

        // For source files, create an entry for the primary function
        if is_source {
            let info = FunctionInfo {
                in_header: false,
                in_source: true,
                has_gpm_directive: false,
            };
            functions.insert(filename.clone(), info);
            debug!("Added function from filename: {}", filename);
        }

        // Scan file content line by line
        for line in content.lines() {
            // Look for function declarations (especially in headers)
            if let Some(captures) = fn_decl.captures(line) {
                let fn_name = captures[1].to_string();
                let info = functions.entry(fn_name.clone()).or_insert(FunctionInfo {
                    in_header: is_header,
                    in_source: is_source,
                    has_gpm_directive: false,
                });
                if is_header {
                    info.in_header = true;
                }
                debug!("Found function declaration: {}", fn_name);
            }

            // Check for GPM directives (@, !)
            if gpm_directive.is_match(line) {
                if let Some(info) = functions.get_mut(&filename) {
                    debug!("Found GPM directive for {}", filename);
                    info.has_gpm_directive = true;
                }
            }
        }

        Ok(functions)
    }

    /// Creates and prints a formatted table of function information
    fn print_table(&self, functions: &HashMap<String, FunctionInfo>) {
        let mut table = Table::new();

        // Configure table format
        let format = format::FormatBuilder::new()
            .column_separator('│')
            .borders('│')
            .separator(
                format::LinePosition::Top,
                format::LineSeparator::new('─', '┬', '╭', '╮'),
            )
            .separator(
                format::LinePosition::Title,
                format::LineSeparator::new('─', '┼', '├', '┤'),
            )
            .separator(
                format::LinePosition::Bottom,
                format::LineSeparator::new('─', '┴', '╰', '╯'),
            )
            .padding(1, 1)
            .build();
        table.set_format(format);
        // table.set_format(*format::consts::FORMAT_NO_LINESEP_WITH_TITLE);

        // Add header row with styled titles
        table.set_titles(Row::new(vec![
            Cell::new("Function Name").style_spec("lb"),
            Cell::new("Header").style_spec("cb"),
            Cell::new("Source").style_spec("cb"),
            Cell::new("GPM Dir.").style_spec("cb"),
        ]));
        // table.set_titles(row![&"Function Name".bold().to_string(), &"Header".bold().to_string(), &"Source".bold().to_string(), &"GPM Dir.".bold().to_string()]);

        // Add function rows
        let mut sorted_fns: Vec<_> = functions.iter().collect();
        sorted_fns.sort_by(|a, b| a.0.cmp(b.0));

        // Helper function to create styled checkmarks
        let status_mark = |condition: bool| -> Cell {
            if condition {
                Cell::new("✓").style_spec("cbFg")
            } else {
                Cell::new("✗").style_spec("cbFr")
            }
        };

        debug!("Printing {} functions", sorted_fns.len());
        for (name, info) in &sorted_fns {
            debug!("Adding row for {}: {:?}", name, info);
            table.add_row(Row::new(vec![
                Cell::new(name).style_spec("l"),
                status_mark(info.in_header),
                status_mark(info.in_source),
                status_mark(info.has_gpm_directive),
            ]));
        }

        // Print the table with a title
        println!("\n{}", "Function Analysis Results:".bold());
        table.printstd();

        // Print summary
        println!("\n{}", "Summary:".bold());
        println!("Total functions: {}", sorted_fns.len());
        println!(
            "With headers: {}",
            sorted_fns
                .iter()
                .filter(|&(_, info)| info.in_header)
                .count()
        );
        println!(
            "With GPM directives: {}",
            sorted_fns
                .iter()
                .filter(|&(_, info)| info.has_gpm_directive)
                .count()
        );
    }
}

impl Command for List {
    fn execute(&mut self) -> anyhow::Result<()> {
        let project_path = self.cwd.join(&self.project_name);

        info!("Analyzing project at: {}", project_path.display());

        // Load project configuration
        let config_manager = PushConfigManager::new();
        let _push_config = config_manager.load_push_config(&project_path)?;

        // Collection to store all found functions
        let mut all_functions: HashMap<String, FunctionInfo> = HashMap::new();

        // Scan all C source and header files in the project
        for entry in WalkDir::new(&project_path) {
            let entry = entry?;
            let path = entry.path().to_path_buf();

            if path.is_file()
                && matches!(path.extension().and_then(|s| s.to_str()), Some("c" | "h"))
            {
                let functions = self.scan_file(&path)?;
                for (name, info) in functions {
                    let existing: &mut FunctionInfo = all_functions.entry(name).or_default();
                    existing.in_header |= info.in_header;
                    existing.in_source |= info.in_source;
                    existing.has_gpm_directive |= info.has_gpm_directive;
                }
            }
        }

        // Display results
        info!("Found {} total functions", all_functions.len());
        self.print_table(&all_functions);

        Ok(())
    }
}
