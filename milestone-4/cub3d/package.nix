{
  inputs,
  lib,
  ...
}: let
  version = lib.trim (builtins.readFile ./version.txt);
in {
  perSystem = {
    pkgs,
    system,
    ...
  }: {
    packages = {
      cub3d = pkgs.stdenv.mkDerivation (finalAttrs: {
        pname = "cub3d";
        inherit version;

        src = ../..;

        buildInputs = with pkgs; [libx11.dev libxext];
        nativeBuildInputs = [pkgs.zig_0_16];
        buildPhase = ''
          runHook preBuild

          cd milestone-4/cub3d
          zig build

          runHook postBuild
        '';

        installPhase = ''
          runHook preInstall

          install -Dvm 755 zig-out/bin/cub3d $out/bin/cub3d
          ln -sv $out/bin/cub3d $out/bin/cub3d-${finalAttrs.version}

          find assets/textures -type f -name '*.xpm' -exec \
            install -Dvm 644 "{}" $out/share/cub3d/textures/ \;
          find assets/maps -type f -name '*.cub' -exec \
            install -Dvm 644 "{}" $out/share/cub3d/maps/ \;
          find $out/share/cub3d/maps -type f -name '*.cub' -exec \
            substituteInPlace "{}" \
              --replace-fail "../../" "../" \;

          runHook postInstall
        '';
      });

      cub3d-3ds = let
        pkgs = import inputs.nixpkgs {
          inherit system;
          overlays = [inputs.devkitNix.overlays.default];
        };
        stdenv = pkgs.devkitNix.stdenvARM;
      in
        stdenv.mkDerivation (finalAttrs: {
          pname = "cub3d-3ds";
          version = builtins.readFile ./version.txt;

          src = ../..;

          buildPhase = ''
            runHook preBuild

            cd milestone-4/cub3d
            bash build_3ds.sh

            runHook postBuild
          '';

          installPhase = ''
            runHook preInstall

            mkdir -pv $out/bin
            install -vm 644 cub3d.3dsx $out/bin/cub3d-${finalAttrs.version}.3dsx
            install -vm 644 cub3d.elf $out/bin/cub3d-${finalAttrs.version}.elf
            install -vm 644 cub3d.smdh $out/bin/cub3d-${finalAttrs.version}.smdh
            ln -sv $out/bin/cub3d.3dsx $out/bin/cub3d-${finalAttrs.version}.3dsx
            ln -sv $out/bin/cub3d.elf $out/bin/cub3d-${finalAttrs.version}.elf
            ln -sv $out/bin/cub3d.smdh $out/bin/cub3d-${finalAttrs.version}.smdh

            runHook postInstall
          '';
        });
    };
  };
}
