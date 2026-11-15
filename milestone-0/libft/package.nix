_: {
  perSystem = {
    config,
    pkgs,
    lib,
    ...
  }: {
    packages.libft = pkgs.stdenv.mkDerivation (finalAttrs: {
      pname = "libft";
      version = builtins.readFile ./version.txt;

      src = ./.;

      nativeBuildInputs = with pkgs; [cmake];

      doCheck = true;
      cmakeFlags = [(pkgs.lib.cmakeBool "BUILD_TESTING" finalAttrs.doCheck)];

      meta = {
        description = "A standard library";
        maintainers = [lib.maintainers.airone01];
        license = lib.licenses.mit;
      };
    });
    checks.libft = config.packages.libft;
  };
}
