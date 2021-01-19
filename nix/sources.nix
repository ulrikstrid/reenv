{ ocamlVersion ? "4_11" }:
let
  overlays =
    builtins.fetchTarball
      https://github.com/ulrikstrid/nix-overlays/archive/066d13cfb40f57ee3ce7969039dd87cd66ceed3d.tar.gz;

in
import "${overlays}/sources.nix" {
  overlays = [
    (import overlays)
    (self: super: {
      ocamlPackages = super.ocaml-ng."ocamlPackages_${ocamlVersion}";

      pkgsCross.musl64.pkgsStatic = super.pkgsCross.musl64.pkgsStatic.appendOverlays [
        (self: super: {
          ocamlPackages = super.ocaml-ng."ocamlPackages_${ocamlVersion}";
        })
      ];
    })
  ];
}
