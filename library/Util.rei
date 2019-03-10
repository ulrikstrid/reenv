let readUntilEndOfFile:
  (~previousLines: list(string)=?, in_channel) => list(string);

let trimCitation: string => string;

let escapeEquals: list(string) => (string, string);
