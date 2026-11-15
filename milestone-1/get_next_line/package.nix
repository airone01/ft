_: {
  perSystem = {
    config,
    pkgs,
    lib,
    ...
  }: {
    packages.get_next_line = pkgs.stdenv.mkDerivation {
      pname = "get_next_line";
      version = builtins.readFile ./version.txt;

      src = ./.;

      nativeBuildInputs = [
        pkgs.cmake
        config.packages.libft
      ];

      meta = {
        description = "A text input and processing library";
        maintainers = [lib.maintainers.airone01];
        license = lib.licenses.mit;
      };
    };
  };
}
