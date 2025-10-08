workspace(name = "ft")

# Load HTTP archive rule for fetching external dependencies
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# ============================================================================
# Rust Rules
# ============================================================================
http_archive(
    name = "rules_rust",
    sha256 = "b8cd5a9d7e3f6e7212b0e0b7fd08bb2ad0b9dd7eb6c8398c8e7e9fb82d07e3e2",
    urls = [
        "https://github.com/bazelbuild/rules_rust/releases/download/0.53.0/rules_rust-v0.53.0.tar.gz",
    ],
)

load("@rules_rust//rust:repositories.bzl", "rules_rust_dependencies", "rust_register_toolchains")
rules_rust_dependencies()
rust_register_toolchains(
    edition = "2021",
    versions = ["1.90.0"],
)

# ============================================================================
# C++ Rules (built-in, but we can configure cc_toolchain if needed)
# ============================================================================

# ============================================================================
# External Libraries
# ============================================================================

# Note from LLM:
# MiniLibX for graphical projects (if needed as external dependency)
# You may need to create a BUILD file for this or keep it as a local library
