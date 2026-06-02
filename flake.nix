{
  description = "ft monorepo";

  inputs = {
    devkitNix.url = "github:bandithedoge/devkitNix";
    flake-parts.url = "github:hercules-ci/flake-parts";
    git-hooks.url = "github:cachix/git-hooks.nix";
    import-tree.url = "github:vic/import-tree";
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    systems.url = "github:nix-systems/default";
    treefmt-nix.url = "github:numtide/treefmt-nix";
  };

  outputs = inputs: let
    inherit (inputs.nixpkgs) lib;
  in
    inputs.flake-parts.lib.mkFlake
    {inherit inputs;}
    (lib.pipe inputs.import-tree [
      (i: i.filterNot (lib.hasInfix "/external-tools/"))
      (i: i.filterNot (lib.hasSuffix "/flake.nix"))
      (i: i ./.)
    ]);
}
