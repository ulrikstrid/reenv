type t;

let make: list(string) => t;

let to_array: t => array(string);
let to_tuple_list: t => list((string, string));

let get_env: (string, t) => string;
