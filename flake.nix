# ============================================================================ #
#                             BAZEL FHS WORKAROUND                             #
# Bazel downloads pre-compiled binaries that expect standard Linux paths (like #
# `/lib64`). On NixOS, these crash with a 'stub-ld' error.                     #
#                                                                              #
# This is only ever a problem for certain tasks that run something that was    #
# just compiled, in particular the 'refresh_compile_commands' target in this   #
# repo, which builds a set of scripts that can be run to generate the          #
# 'compile_commands.json' file. (see REAME.md)                                 #
#                                                                              #
# I use `steam-run bazel` locally to fake a standard filesystem so             #
# they execute, keeping the repo pure for 42's Ubuntu.                         #
# The alternatives are too complicated for what I'm bothered to code (if even  #
# possible in the case of 'refresh_compile_commands').                         #
# I have not included 'steam-run' in this flake as it is unfree software.      #
#                                                                              #
# If you decide to go the 'steam-run' route like me to generate                #
# 'compile_commands.json', you can safely ignore the 'launcher_maker.cc'       #
# warnings that Bazel yells at you.                                            #
#                                                                              #
# Those are caused by Hedron aggressively trying to analyze *everything* in    #
# the dependency graph so the LSP has perfect score, which fails because       #
# Bazel's internal C++ script does not pass `--std=c++11` to its own internal  #
# tooling. Basically nothing to worry about.                                   #
# ============================================================================ #
{
  description = "Flake for ft";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    c_formatter_42.url = "github:maix-flake/c_formatter_42";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    c_formatter_42,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};

      combinedX11 = pkgs.runCommand "combined-x11-headers" {} ''
        mkdir -p $out/X11/extensions
        cp -r ${pkgs.libX11.dev}/include/X11/* $out/X11/
        cp -r ${pkgs.libXext.dev}/include/X11/extensions/* $out/X11/extensions/
      '';
    in {
      devShells.default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          bashInteractive
        ];
        buildInputs = with pkgs; [
          bazel_8

          # Node tools
          nodejs_22
          bun
          openssl
          lld

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
          libX11.dev
          libXext.dev
          libbsd
        ];

        shellHook = ''
          export PATH="$PWD/node_modules/.bin/:$PATH"
          export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.stdenv.cc.cc.lib}/lib:${pkgs.libX11.dev}/lib"

          # minilibx
          export X11_LIB_PATH="${combinedX11}"
          echo "Starting configure script modification..."
          if [[ -f ./extra-minilibx/configure ]]; then
            echo "Configure file exists"
            ls -l ./extra-minilibx/configure  # Check permissions

            if ! grep -q "\$X11_LIB_PATH" ./extra-minilibx/configure; then
              echo "Line not found, attempting to add it"

              # Try to make the file writable if it isn't
              chmod u+w ./extra-minilibx/configure

              # Print the matched line count to verify our sed pattern
              echo "Lines matching 'for inc in': $(grep -c "for inc in \\\\" ./extra-minilibx/configure)"

              sed -i '/for inc in \\/ a\		$X11_LIB_PATH          \\' ./extra-minilibx/configure

              echo "Modification attempted. Checking if line was added:"
              grep "\$X11_LIB_PATH" ./extra-minilibx/configure || echo "Line not found after modification!"
            else
              echo "Line already exists"
            fi
          else
            echo "Configure file not found!"
          fi
        '';
      };
    });
}
