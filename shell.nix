{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.cmake
    pkgs.boost
    pkgs.wireshark-cli # For debugging
  ];

  shellHook = ''
    exec fish
  '';
}

