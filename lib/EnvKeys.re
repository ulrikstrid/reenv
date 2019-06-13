module SS = Set.Make(String);

type t = SS.t;

let list_of_in_channel = ic => {
  Util.readUntilEndOfFile(ic)
  |> List.map(row =>
       switch (String.split_on_char('=', row)) {
       | [key, ..._] => key
       | [] => ""
       }
     )
  |> List.filter(a => a != "");
};

let make = file => {
  let t = file |> open_in_bin |> list_of_in_channel |> SS.of_list;
  if (SS.is_empty(t)) {
    SS.empty;
  } else {
    t;
  };
};

let concat = t_list => {
  t_list |> List.map(SS.elements) |> List.concat |> SS.of_list;
};

let has_key = (t, key) => {
  SS.exists(elt => elt == key, t);
};

let equal = SS.equal;

let missing_keys = (t1, t2) => {
  // TODO: is this right?
  SS.union(t1, t2) |> SS.elements;
};
