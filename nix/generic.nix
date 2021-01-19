{ pkgs, stdenv, lib, ocamlPackages, static ? false, doCheck }:

with ocamlPackages;

rec {
  reenv = buildDunePackage {
    pname = "reenv";
    version = "0.3.1-dev";

    src = lib.filterGitSource {
      src = ./..;
      dirs = [ "lib" "executable" "test" ];
      files = [ "dune-project" "oidc.opam" ];
    };

    useDune2 = true;

    propagatedBuildInputs = [
      reason
      cmdliner
      re
    ];

    buildInputs = [
      alcotest
      junit
      junit_alcotest
    ];

    inherit doCheck;

    meta = {
      description = "dotenv-cli written in reason";
      license = stdenv.lib.licenses.bsd3;
    };
  };
}
