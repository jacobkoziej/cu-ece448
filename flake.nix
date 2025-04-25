{
  description = "The Cooper Union - ECE 448: Power Electronics";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    jacobkoziej = {
      url = "github:jacobkoziej/nur-packages";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs =
    inputs:

    inputs.flake-utils.lib.eachDefaultSystem (
      system:

      let
        pkgs = import inputs.nixpkgs {
          inherit system;
        };

        inherit (pkgs) lib;

      in
      {
        devShells.default = pkgs.mkShell (
          let
            pre-commit-bin = "${lib.getBin pkgs.pre-commit}/bin/pre-commit";

            pkgs-jacobkoziej = inputs.jacobkoziej.legacyPackages.${system};

            inherit (pkgs-jacobkoziej.raspberry-pi) openocd;

          in
          {
            packages = with pkgs; [
              cmake
              gcc-arm-embedded
              mdformat
              ninja
              openocd
              picotool
              pre-commit
              shfmt
              toml-sort
              treefmt
              yamlfmt
              yamllint
            ];

            shellHook = ''
              ${pre-commit-bin} install --allow-missing-config > /dev/null
            '';
          }
        );

        formatter = pkgs.nixfmt-rfc-style;
      }
    );
}
