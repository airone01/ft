{
  description = "Flake for ft";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    c_formatter_42.url = "github:maix-flake/c_formatter_42";
  };

  outputs = { nixpkgs, flake-utils, c_formatter_42, ... }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.default = pkgs.mkShell {
        nativeBuildInputs = [ pkgs.bashInteractive ];
        buildInputs = with pkgs; [
          # Node tools
          nodejs_22
          bun
          openssl
          lld

          # Sharp
          stdenv.cc.cc.lib

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
        ];
        shellHook = with pkgs; ''
          export PATH="$PWD/node_modules/.bin/:$PATH"
          # Sharp
          export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.stdenv.cc.cc.lib}/lib:"
        '';
      };
    });
}
