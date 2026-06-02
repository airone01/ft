{inputs, ...}: {
  perSystem = {system, ...}: let
    pkgs = import inputs.nixpkgs {
      inherit system;
      overlays = [inputs.devkitNix.overlays.default];
    };
  in {
    devShells.threeDS =
      pkgs.mkShell.override {
        stdenv = pkgs.devkitNix.stdenvARM;
      } {
        packages = [pkgs.azahar];
      };
  };
}
