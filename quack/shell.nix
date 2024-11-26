{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    # Rust tools
    rustc
    cargo
    rustfmt
    clippy
    wasm-pack

    # Build tools
    gcc
    gcc-unwrapped
    lld

    # Required for WASM compilation
    stdenv.cc.cc.lib

    # Additional build dependencies
    pkg-config
    openssl

    # WASM specific
    binaryen # for wasm-opt

    # Optional but recommended
    rust-analyzer # IDE support
  ];

  # Required for certain Rust tools
  RUST_SRC_PATH = "${pkgs.rust.packages.stable.rustPlatform.rustLibSrc}";

  # Ensure libstdc++ is available
  LD_LIBRARY_PATH = "${pkgs.stdenv.cc.cc.lib}/lib";

  # Add any other environment variables needed
  shellHook = ''
    echo "Rust + WASM development environment loaded"
  '';
}
