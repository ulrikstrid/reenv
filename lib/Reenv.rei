module Util = Util;
module Env = Env;

exception Missing_keys(string);

let checkSafe: (~safeFile: string, list(string)) => unit;

let main:
  (
    ~envFiles: list(string),
    ~safeFile: option(string),
    ~command: string,
    list(string)
  ) =>
  'a;
