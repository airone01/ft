{
  description = "Flake for ft";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    c_formatter_42.url = "github:maix-flake/c_formatter_42";
    devkitNix.url = "github:bandithedoge/devkitNix";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    c_formatter_42,
    devkitNix,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
        overlays = [devkitNix.overlays.default];
      };
    in {
      devShells.default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          bashInteractive
        ];
        buildInputs = with pkgs; [
          # ASM
          nasm

          # Rust
          pkg-config
          rustc
          cargo
          gcc
          rustfmt
          clippy

          # 42
          c_formatter_42.packages.${system}.default
          norminette
          valgrind

          # X11
          libX11
          libX11.dev
          libXext
          libXext.dev

          # minishell
          readline

          just
        ];
      };

      devShells.threeDS =
        pkgs.mkShell.override {
          stdenv = pkgs.devkitNix.stdenvARM;
        } {
          packages = [
            pkgs.azahar
          ];
        };
    });
}
