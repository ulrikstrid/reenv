open Re;

let rec readUntilEndOfFile = (~previousLines=[], in_channel) =>
  try (
    {
      let row = input_line(in_channel);
      let lines =
        switch (String.trim(row)) {
        | "" => previousLines
        | r when String.unsafe_get(r, 0) == '#' => previousLines
        | r => [r, ...previousLines]
        };
      readUntilEndOfFile(~previousLines=lines, in_channel);
    }
  ) {
  | End_of_file => List.rev(previousLines)
  };

let trimCitation = str =>
  try (
    exec(Perl.compile_pat("(^[\'\"])(.*)[\'\"]$"), str)
    |> (g => Group.get(g, 2))
  ) {
  | Not_found => str
  };

let escapeEquals = line =>
  switch (line) {
  | [name, ...value] =>
    let fixedValue =
      value
      |> String.concat("=")
      |> trimCitation
      |> Str.global_replace(Str.regexp("\\\\n"), "\n")
      |> String.trim;

    (name, fixedValue);
  | [] => ("", "") // This should never happen
  };
