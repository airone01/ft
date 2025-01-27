{
  description = "Flake for ft";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.default = pkgs.mkShell {
        nativeBuildInputs = [ pkgs.bashInteractive ];
        buildInputs = with pkgs; [
          # Node tools
          nodejs_18
          bun
          nodePackages.prisma
          openssl
          lld

          # Prisma
          prisma-engines

          # Sharp
          stdenv.cc.cc.lib

          # Rust
          pkg-config
          rustc
          cargo
          gcc
          rustfmt
          clippy
        ];
        shellHook = with pkgs; ''
          # Prisma
          export PRISMA_SCHEMA_ENGINE_BINARY="${prisma-engines}/bin/schema-engine"
          export PRISMA_QUERY_ENGINE_BINARY="${prisma-engines}/bin/query-engine"
          export PRISMA_QUERY_ENGINE_LIBRARY="${prisma-engines}/lib/libquery_engine.node"
          # https://www.prisma.io/docs/orm/more/under-the-hood/engines
          #export PRISMA_INTROSPECTION_ENGINE_BINARY="${prisma-engines}/bin/introspection-engine"
          export PRISMA_FMT_BINARY="${prisma-engines}/bin/prisma-fmt"
          export PATH="$PWD/node_modules/.bin/:$PATH"
          # Sharp
          export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.stdenv.cc.cc.lib}/lib:"
        '';
      };
    });
}
