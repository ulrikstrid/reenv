let main = argv => {
  switch (argv) {
  | [_, envFile, program, ...programArgs] =>
    let programArgs = Array.of_list([program, ...programArgs]);

    Util.readUntilEndOfFile(open_in_bin(envFile))
    |> List.filter(s => String.contains(s, '='))
    |> List.map(String.split_on_char('='))
    |> List.map(([name, ...value]) => {
         let fixedValue =
           value
           |> String.concat("=")
           |> Util.trimCitation
           |> Util.replaceNewline;
         name ++ "=" ++ fixedValue;
       })
    |> Array.of_list
    |> Array.append(Unix.environment())
    |> Unix.execvpe(program, programArgs);
  | _ =>
    at_exit(() => print_endline("Not enough arguments"));
    exit(1);
  };
};

module Util = Util;
