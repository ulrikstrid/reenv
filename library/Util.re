let rec readUntilEndOfFile = (~previousLines=[], in_channel) =>
  try (
    readUntilEndOfFile(
      ~previousLines=[input_line(in_channel), ...previousLines],
      in_channel,
    )
  ) {
  | End_of_file => previousLines
  };

let trimCitation = str =>
  // If we find a " in the start, assume it's one in the end as well
  if (str.[0] == '"') {
    let len = String.length(str);
    String.sub(str, 1, len - 2);
  } else {
    str;
  };

let replaceNewline = str => {
  Str.global_replace(Str.regexp("\\\\n"), "\n", str);
};
