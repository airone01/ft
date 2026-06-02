_: let
  treefmtExcludes = [
    "CHANGELOG.md"
    ".release-please-manifest.json"
    "**/*.html"
  ];
  preCommitExcludes = [
    "CHANGELOG\\.md$"
    "\\.release-please-manifest\\.json$"
    ".*\.html$"
  ];
in {
  perSystem = {
    pkgs,
    config,
    ...
  }: {
    pre-commit = {
      check.enable = true;
      settings = {
        excludes = preCommitExcludes;
        hooks.treefmt.enable = true;
      };
    };

    treefmt = {
      projectRootFile = "flake.nix";
      settings.global.excludes = treefmtExcludes;

      programs = {
        alejandra.enable = true;
        clang-format.enable = true;
        deadnix.enable = true;
        statix.enable = true;
        taplo.enable = true;
      };
    };

    devShells.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        # ASM
        nasm

        # Rust
        pkg-config
        rustc
        cargo
        gcc
        rustfmt

        # 42
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
      shellHook = config.pre-commit.installationScript;
    };
  };
}
