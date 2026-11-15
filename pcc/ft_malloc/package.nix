_: {
  perSystem = {
    lib,
    pkgs,
    ...
  }: {
    packages.ft_malloc = pkgs.stdenv.mkDerivation {
      pname = "ft_malloc";
      version = builtins.readFile ./version.txt;

      src = ./.;

      nativeBuildInputs = [pkgs.cmake];

      meta = {
        description = "A malloc(3) clone without brk(3)";
        maintainers = [lib.maintainers.airone01];
        license = lib.licenses.mit;
      };
    };
  };
}
