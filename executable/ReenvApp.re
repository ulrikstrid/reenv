open Cmdliner;

let envFiles = {
  let doc = "The .env files to read variables from.";
  Arg.(
    value
    & opt_all(non_dir_file, [])
    & info(["e", "env-file"], ~docv="FILE", ~doc)
  );
};

let safeFile = {
  let doc = "The .env file with keys that need to be provided.";
  Arg.(
    value
    & opt(some(non_dir_file), None)
    & info(["s", "safe"], ~docv="FILE", ~doc)
  );
};

let command = {
  let doc = "Command to run";
  Arg.(
    required
    & pos(~rev=false, 0, some(string), None)
    & info([], ~docv="COMMAND", ~doc)
  );
};

let args = {
  let doc = "Arguments passed to the command.";
  Arg.(
    value
    & pos_right(~rev=false, 0, string, [])
    & info([], ~docv="ARGS", ~doc)
  );
};

let start = (envFiles, safeFile, command, args) => {
  Reenv.main(~envFiles, ~safeFile, ~command, args);
};

let () = {
  let doc = "Read dotenv file(s) and supply them to the program.";
  let man = [
    `S(Manpage.s_bugs),
    `P("File an issue athttps://github.com/ulrikstrid/reenv/issues"),
  ];
  let term = Term.(const(start) $ envFiles $ safeFile $ command $ args);
  let info =
    Term.info(
      "reenv",
      ~doc,
      ~man,
      ~version="0.3.0",
      ~exits=Term.default_exits,
    );

  (term, info) |> Term.eval |> Term.exit;
};
