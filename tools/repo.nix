_: let
  treefmtExcludes = [
    "CHANGELOG.md"
    ".release-please-manifest.json"
    "**/*.html"
    "**.envrc"
    "pcc/ft_linux/downloads/check_host_deps.sh"
    "pcc/snow-crash/auto.sh"
    "central/minilibx/**/*.sh"
    "milestone-4/cpp00/ex01/test.sh"
  ];
  preCommitExcludes = [
    "CHANGELOG\\.md$"
    "\\.release-please-manifest\\.json$"
    ".*\\.html$"
    ".*\\.envrc$"
    "pcc/ft_linux/downloads/check_host_deps.sh$"
    "pcc/snow-crash/auto.sh$"
    "central/minilibx/test/.*\\.sh$"
    "milestone-4/cpp00/ex01/test\\.sh$"
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
        # c, cpp
        clang-format.enable = true;
        # nix
        alejandra.enable = true;
        deadnix.enable = true;
        statix.enable = true;
        # toml
        taplo.enable = true;
        # zig
        zig.enable = true;
        # shell
        shellcheck.enable = true;
        # yaml
        yamlfmt.enable = true;
        # rust
        rustfmt.enable = true;
      };
    };

    devShells.default = pkgs.mkShell {
      nativeBuildInputs = with pkgs; [
        cmake
        ninja
        just
        pkg-config
      ];
      buildInputs = with pkgs; [
        # Compilers
        nasm
        bison
        flex
        gcc

        # Rust
        rustc
        cargo
        rustfmt

        # Libs
        readline # for minishell
        ## X11
        libx11
        libx11.dev
        libxext
        libxext.dev
        xorgproto # needed by FindX11.cmake

        # Test
        valgrind
      ];
      shellHook = config.pre-commit.installationScript;
    };
  };
}
