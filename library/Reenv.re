type t = Hashtbl.t(string, string);

let t_of_in_channel = (t, ic) => {
  Util.readUntilEndOfFile(ic)
  |> List.filter(s => String.contains(s, '='))
  |> List.map(String.split_on_char('='))
  |> List.map(Util.escapeEquals)
  |> List.iter(((key, value)) => Hashtbl.replace(t, key, value));

  t;
};

let array_of_t: t => array(string) =
  t => {
    Hashtbl.fold((key, value, l) => [key ++ "=" ++ value, ...l], t, [])
    |> Array.of_list;
  };

let make = (): t => Hashtbl.create(64);

let get_opt = (key, t) => Hashtbl.find_opt(t, key);
let get_exn = (key, t) => Hashtbl.find(t, key);

let main = (~envFiles, ~command, argv) => {
  let programArgs = Array.of_list([command, ...argv]);

  let t: t = make();

  Unix.environment()
  |> Array.map(s =>
       switch (String.split_on_char('=', s)) {
       | [key, ...value] => (key, String.concat("", value))
       | _ => exit(1)
       }
     )
  |> Array.iter(((key, value)) => Hashtbl.replace(t, key, value));

  envFiles
  |> List.map(open_in_bin)
  |> List.iter(ic => t_of_in_channel(t, ic) |> ignore);

  try (Unix.execvpe(command, programArgs, array_of_t(t))) {
  | Unix.Unix_error(error, _method, _program) =>
    print_endline("Got error: " ++ Unix.error_message(error));
    exit(1);
  };
};

module Util = Util;
