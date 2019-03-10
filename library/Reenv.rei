module Util = Util;

type t;

let make: unit => t;

let get_opt: (string, t) => option(string);
let get_exn: (string, t) => string;

let array_of_t: t => array(string);

let main: (~envFiles: list(string), ~command: string, list(string)) => 'a;

let t_of_in_channel: (t, in_channel) => t;
