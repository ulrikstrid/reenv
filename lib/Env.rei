type t;

let make: list(string) => t;

let to_array: t => array(string);

let get_env: (string, t) => string;
