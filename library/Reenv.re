let main = argv => {
  switch (argv) {
  | [_, envFile, program, ...programArgs] =>
    let programArgs = Array.of_list([program, ...programArgs]);

    Util.readUntilEndOfFile(open_in_bin(envFile))
    |> List.filter(s => String.contains(s, '='))
    |> List.map(String.split_on_char('='))
    |> List.map(l =>
         switch (l) {
         | [name, ...value] =>
           let fixedValue =
             value
             |> String.concat("=")
             |> Util.trimCitation
             |> Util.replaceNewline;
           name ++ "=" ++ fixedValue;
         | [] => String.concat("", l) // This should never happen
         }
       )
    |> Array.of_list
    |> Array.append(Unix.environment())
    |> (
      env =>
        try (Unix.execvpe(program, programArgs, env)) {
        | Unix.Unix_error(error, _method, _program) =>
          print_endlie("Got error: " ++ Unix.error_message(error));
          exit(1);
        }
    );
  | _ =>
    print_endline("Not enough arguments");
    exit(1);
  };
};

module Util = Util;
