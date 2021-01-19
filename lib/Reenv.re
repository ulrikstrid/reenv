exception Missing_keys(string);

let checkSafe = (~safeFile, envFiles) => {
  let envKeys = envFiles |> List.map(EnvKeys.make) |> EnvKeys.concat;

  let safeKeys = EnvKeys.make(safeFile);

  if (EnvKeys.equal(envKeys, safeKeys)) {
    ();
  } else {
    EnvKeys.missing_keys(envKeys, safeKeys)
    |> String.concat(", ")
    |> (keyString => raise(Missing_keys(keyString)));
  };
};

let get_environment = (~safeFile=?, ~envFiles) => {
  let () =
    switch (safeFile) {
    | Some(safeFile) => checkSafe(~safeFile, envFiles)
    | None => ()
    };

  let environment = Env.make(envFiles) |> Env.to_array;

  environment;
};

let main = (~safeFile=?, ~envFiles, ~command, argv) => {
  let programArgs = Array.of_list([command, ...argv]);
  let environment = get_environment(~envFiles, ~safeFile?);

  try(Unix.execvpe(command, programArgs, environment)) {
  | Unix.Unix_error(error, _method, _program) =>
    print_endline("Got error: " ++ Unix.error_message(error));
    exit(1);
  };
};

module Util = Util;
module Env = Env;
