{inputs, ...}: {
  perSystem = {system, ...}: let
    pkgs = import inputs.nixpkgs {
      inherit system;
      overlays = [inputs.devkitNix.overlays.default];
    };
    stdenv = pkgs.devkitNix.stdenvARM;
  in {
    packages = {
      cub3d-3ds = stdenv.mkDerivation {
        pname = "cub3d-3ds";
        version = "1.0.0";

        src = ../..;

        buildPhase = ''
          cd milestone-4/cub3d
          bash build_3ds.sh
        '';

        installPhase = ''
          mkdir -p $out/bin
          cp cub3d.3dsx $out/bin/
          cp cub3d.elf $out/bin/
          cp cub3d.smdh $out/bin/
        '';
      };
    };
  };
}
