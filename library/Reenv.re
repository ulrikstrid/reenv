exception Missing_keys(string);

type t = Hashtbl.t(string, string);

let t_of_in_channel = (t, ic) => {
  Util.readUntilEndOfFile(ic)
  |> List.filter(s => String.contains(s, '='))
  |> List.map(String.split_on_char('='))
  |> List.map(Util.escapeEquals)
  |> List.iter(((key, value)) => Hashtbl.replace(t, key, value));

  t;
};

let array_of_t: t => array((string, string)) =
  t => {
    Hashtbl.fold((key, value, l) => [(key, value), ...l], t, [])
    |> Array.of_list;
  };

let make = (): t => Hashtbl.create(64);

let get_opt = (key, t) => Hashtbl.find_opt(t, key);
let get_exn = (key, t) => Hashtbl.find(t, key);

let checkSafe = (~safeFile, t) => {
  let safeEnv = safeFile |> open_in_bin |> t_of_in_channel(make());

  array_of_t(safeEnv)
  |> Array.fold_left(
       (lst, (key, _value)) =>
         switch (get_opt(key, t)) {
         | Some(_v) => lst
         | None => [key, ...lst]
         },
       [],
     )
  |> (
    keys =>
      switch (keys) {
      | [] => ()
      | lst => Missing_keys(String.concat(", ", lst)) |> raise
      }
  );
};

let main = (~envFiles, ~safeFile, ~command, argv) => {
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

  let () =
    switch (safeFile) {
    | Some(safeFile) => checkSafe(~safeFile, t)
    | None => ()
    };

  let environment =
    array_of_t(t) |> Array.map(((key, value)) => key ++ "=" ++ value);

  try (Unix.execvpe(command, programArgs, environment)) {
  | Unix.Unix_error(error, _method, _program) =>
    print_endline("Got error: " ++ Unix.error_message(error));
    exit(1);
  };
};

module Util = Util;
