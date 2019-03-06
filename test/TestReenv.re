open TestFramework;

describe("readUntilEndOfFile", utils =>
  utils.test("should read all lines corectly", ({expect}) => {
    let file = open_in_bin("./test/.env");
    let rows = Reenv.Util.readUntilEndOfFile(file);

    expect.list(rows).toEqual([
      {|TEST="hello world!"|},
      {|TEST2=hello world?|},
      {|TEST3="hello=world"|},
    ]);
  })
);

describe("dotenv-cli rules", utils => {
  utils.test("empty lines are skipped", ({expect}) => {
    let file = open_in_bin("./test/.env.with_empty_line");
    let rows = Reenv.Util.readUntilEndOfFile(file);

    expect.int(List.length(rows)).toBe(2);
  });

  utils.test("BASIC=basic is same as BASIC=\"basic\"", ({expect}) => {
    let file = open_in_bin("./test/.env.with_comment");
    let rows = Reenv.Util.readUntilEndOfFile(file);

    expect.int(List.length(rows)).toBe(2);
  });

  utils.test("BASIC=basic is same as BASIC=\"basic\"", ({expect}) => {
    let env =
      open_in_bin("./test/.env.quotes")
      |> Reenv.tOfInChannel
      |> Reenv.arrayOft;

    let first = env[0];
    let second = env[1];

    expect.string(first).toEqual(second);
  });

  utils.test(
    "empty values become empty strings (EMPTY= becomes EMPTY=\"\")",
    ({expect}) => {
    let env =
      open_in_bin("./test/.env.empty") |> Reenv.tOfInChannel |> Reenv.arrayOft;

    let first = env[0];
    let second = env[1];

    expect.string(first).toEqual(second);
  });

  utils.test(
    "single and double quoted values are escaped (SINGLE_QUOTE='quoted' == SINGLE_QUOTE=\"quoted\")",
    ({expect}) => {
      let env =
        open_in_bin("./test/.env.single_quotes")
        |> Reenv.tOfInChannel
        |> Reenv.arrayOft;

      let first = env[0];
      let second = env[1];

      expect.string(first).toEqual(second);
    },
  );

  utils.test("whitespace is removed from both ends of the value", ({expect}) => {
    let env =
      open_in_bin("./test/.env.trim") |> Reenv.tOfInChannel |> Reenv.arrayOft;

    let first = env[0];
    let second = env[1];

    expect.string(first).toEqual(second);
  });

  utils.test(
    "inner quotes are maintained (think JSON) (JSON={\"foo\": \"bar\"} becomes {JSON:\"{\\\"foo\\\": \\\"bar\\\"}\")",
    ({expect}) => {
      let env =
        open_in_bin("./test/.env.json")
        |> Reenv.tOfInChannel
        |> Reenv.arrayOft;

      let first = env[0];

      expect.string(first).toEqual("JSON={\"foo\": \"bar\"}");
    },
  );

  utils.test("new lines are expanded", ({expect}) => {
    let env =
      open_in_bin("./test/.env.new_line")
      |> Reenv.tOfInChannel
      |> Reenv.arrayOft;

    let first = env[0];

    expect.string(first).toEqual({|NEW_LINE=new
line|});
  });
});

TestFramework.cli();
