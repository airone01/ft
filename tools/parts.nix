{inputs, ...}: {
  imports = [
    inputs.git-hooks.flakeModule
    inputs.treefmt-nix.flakeModule
  ];

  config = {
    systems = [
      "x86_64-linux"
      # "x86_64-darwin"
      "aarch64-linux"
      # "aarch64-darwin"
    ];
  };
}
