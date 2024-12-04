{
  description = "STUN server with testing";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs";

  outputs = { self, nixpkgs }: {
    devShells.default = nixpkgs.legacyPackages.${system}: pkgs.mkShell {
      buildInputs = [
        pkgs.cmake
        pkgs.gcc
        pkgs.boost
        pkgs.catch2
      ];
    };
  };
}

