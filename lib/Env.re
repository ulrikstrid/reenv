let windows = Sys.os_type == "Win32";

let caseInsensitiveEqual = (i, j) =>
  String.lowercase_ascii(i) == String.lowercase_ascii(j);
let caseInsensitiveHash = k => Hashtbl.hash(String.lowercase_ascii(k));

module EnvHash = {
  type t = string;
  let equal = if (windows) {caseInsensitiveEqual} else {(==)};
  let hash = if (windows) {caseInsensitiveHash} else {Hashtbl.hash};
};

module EnvHashtbl = Hashtbl.Make(EnvHash);

type t = EnvHashtbl.t(string);

let list_of_in_channel = ic => {
  Util.readUntilEndOfFile(ic)
  |> List.filter(s => String.contains(s, '='))
  |> List.map(String.split_on_char('='))
  |> List.map(Util.escapeEquals);
};

let make = envFiles => {
  let fileEnv =
    envFiles
    |> List.map(open_in_bin)
    |> List.map(list_of_in_channel)
    |> List.concat
    |> Array.of_list
    |> Array.map(((key, value)) => key ++ "=" ++ value);

  let curEnv = Unix.environment() |> Array.append(fileEnv);

  let table = EnvHashtbl.create(Array.length(curEnv));
  let f = item =>
    try({
      let idx = String.index(item, '=');
      let name = String.sub(item, 0, idx);
      let value = String.sub(item, idx + 1, String.length(item) - idx - 1);

      let nextValue =
        EnvHashtbl.find_opt(table, name)
        |> (
          fun
          | Some(prevValue) => String.concat(":", [prevValue, value])
          | None => value
        );

      EnvHashtbl.replace(table, name, nextValue);
    }) {
    | Not_found => ()
    };

  Array.iter(f, curEnv);
  table;
};

let to_array = env => {
  let f = (name, value, items) => [name ++ "=" ++ value, ...items];
  let e = Array.of_list(EnvHashtbl.fold(f, env, []));

  e;
};

let to_tuple_list = env => {
  let f = (name: string, value: string, items) => [(name, value), ...items];
  EnvHashtbl.fold(f, env, []);
};

let get_env = (key, env) => {
  EnvHashtbl.find(env, key);
};
