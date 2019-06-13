type t;

let make: string => t;

let concat: list(t) => t;

let has_key: (t, string) => bool;

let equal: (t, t) => bool;

let missing_keys: (t, t) => list(string);
