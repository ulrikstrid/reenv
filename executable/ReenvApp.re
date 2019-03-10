[@deriving (cmdliner, show)]
type params = {
  [@pos 0] [@docv "CMD"]
  command: string,
  [@pos 1] [@docv "ARGS"]
  args: list(string),
  [@opt_all] [@name "e"] [@docv "env file"] [@default [".env"]]
  envFiles: list(string),
};

let start = ({envFiles, command, args}) =>
  Reenv.main(~envFiles, ~command, args);

{
  let term = Cmdliner.Term.(const(start) $ params_cmdliner_term());
  let info = Cmdliner.Term.info(Sys.argv[0]);

  Cmdliner.Term.eval((term, info));
};
