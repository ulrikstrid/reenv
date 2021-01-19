module Util = Util;
module Env = Env;

exception Missing_keys(string);

let checkSafe: (~safeFile: string, list(string)) => unit;

let get_environment:
  (~safeFile: string=?, ~envFiles: list(string)) => array(string);

let main:
  (
    ~safeFile: string=?,
    ~envFiles: list(string),
    ~command: string,
    list(string)
  ) =>
  'a;
