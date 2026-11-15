_: {
  perSystem = {
    pkgs,
    lib,
    ...
  }: {
    packages.minilibx = pkgs.stdenv.mkDerivation {
      pname = "minilibx";
      version = "0.0.0";

      src = ./.;

      nativeBuildInputs = with pkgs; [
        cmake
        libx11.dev
        libxext.dev
        xorgproto
      ];
      buildInputs = with pkgs; [
        libx11
        libxext
      ];

      meta = {
        description = "A text output and processing library";
        maintainers = [lib.maintainers.airone01];
        license = lib.licenses.mit;
      };
    };
  };
}
