_: {
  perSystem = {
    config,
    lib,
    pkgs,
    ...
  }: {
    packages.libasm = pkgs.stdenv.mkDerivation (finalAttrs: {
      pname = "libasm";
      version = builtins.readFile ./version.txt;

      src = ./.;

      nativeBuildInputs = [pkgs.cmake pkgs.nasm];

      doCheck = true;
      cmakeFlags = [(pkgs.lib.cmakeBool "BUILD_TESTING" finalAttrs.doCheck)];

      meta = {
        description = "A standard library in System V AMD64 assembly";
        maintainers = [lib.maintainers.airone01];
        license = lib.licenses.mit;
      };
    });
    checks.libasm = config.packages.libasm;
  };
}
