type t = array(string);

let tOfInChannel = ic =>
  Util.readUntilEndOfFile(ic)
  |> List.filter(s => String.contains(s, '='))
  |> List.map(String.split_on_char('='))
  |> List.map(Util.escapeEquals)
  |> Array.of_list;

let arrayOft: t => array(string) = t => t;

let main = argv => {
  switch (argv) {
  | [_, envFile, program, ...programArgs] =>
    let programArgs = Array.of_list([program, ...programArgs]);

    open_in_bin(envFile)
    |> tOfInChannel
    |> Array.append(Unix.environment())
    |> (
      env =>
        try (Unix.execvpe(program, programArgs, env)) {
        | Unix.Unix_error(error, _method, _program) =>
          print_endline("Got error: " ++ Unix.error_message(error));
          exit(1);
        }
    );
  | _ =>
    print_endline("Not enough arguments");
    exit(1);
  };
};

module Util = Util;
