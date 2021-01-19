let
  pkgs = import ./nix/sources.nix { };
  inherit (pkgs) lib;
  reenvPkgs = pkgs.recurseIntoAttrs (import ./nix { inherit pkgs; }).native;
  reenvDrvs = lib.filterAttrs (_: value: lib.isDerivation value) reenvPkgs;

  filterDrvs = inputs:
    lib.filter
      (drv:
        # we wanna filter our own packages so we don't build them when entering
        # the shell. They always have `pname`
        !(lib.hasAttr "pname" drv) ||
        drv.pname == null ||
        !(lib.any (name: name == drv.pname || name == drv.name) (lib.attrNames reenvDrvs)))
      inputs;
in
with pkgs;

(mkShell {
  inputsFrom = lib.attrValues reenvDrvs;
  buildInputs = with ocamlPackages; [ merlin ocamlformat utop ocaml-lsp ];
}).overrideAttrs (o: {
  propagatedBuildInputs = filterDrvs o.propagatedBuildInputs;
  buildInputs = filterDrvs o.buildInputs;
})
