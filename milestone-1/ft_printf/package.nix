_: {
  perSystem = {
    config,
    pkgs,
    lib,
    ...
  }: {
    packages.ft_printf = pkgs.stdenv.mkDerivation {
      pname = "ft_printf";
      version = builtins.readFile ./version.txt;

      src = ./.;

      nativeBuildInputs = [
        pkgs.cmake
        config.packages.libft
      ];

      meta = {
        description = "A text output and processing library";
        maintainers = [lib.maintainers.airone01];
        license = lib.licenses.mit;
      };
    };
  };
}
