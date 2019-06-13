open TestFramework;

describe("dotenv compliance", utils => {
  utils.test("empty lines are skipped", ({expect}) => {
    let file = open_in_bin("./test/fixtures/.env.with_empty_line");
    let rows = Reenv.Util.readUntilEndOfFile(file);

    expect.int(List.length(rows)).toBe(2);
  });

  utils.test("Skips comments", ({expect}) => {
    let file = open_in_bin("./test/fixtures/.env.with_comment");
    let rows = Reenv.Util.readUntilEndOfFile(file);

    expect.int(List.length(rows)).toBe(2);
  });

  utils.test("BASIC=basic is same as BASIC=\"basic\"", ({expect}) => {
    let env =
      Reenv.Env.make(["./test/fixtures/.env.quotes"])
      |> Reenv.Env.get_env("BASIC");

    expect.string(env).toEqual("basic");
  });

  utils.test(
    "empty values become empty strings (EMPTY= becomes EMPTY=\"\")",
    ({expect}) => {
    let env =
      Reenv.Env.make(["./test/fixtures/.env.empty"])
      |> Reenv.Env.get_env("EMPTY");

    expect.string(env).toEqual("");
  });

  utils.test(
    "single and double quoted values are escaped (SINGLE_QUOTE='quoted' == SINGLE_QUOTE=\"quoted\")",
    ({expect}) => {
      let env =
        Reenv.Env.make(["./test/fixtures/.env.single_quotes"])
        |> Reenv.Env.get_env("SINGLE_QUOTE");

      expect.string(env).toEqual("quoted");
    },
  );

  utils.test("whitespace is removed from both ends of the value", ({expect}) => {
    let env =
      Reenv.Env.make(["./test/fixtures/.env.trim"])
      |> Reenv.Env.get_env("TRIM");

    expect.string(env).toEqual("trim");
  });

  utils.test(
    "inner quotes are maintained (think JSON) (JSON={\"foo\": \"bar\"} becomes {JSON:\"{\\\"foo\\\": \\\"bar\\\"}\")",
    ({expect}) => {
      let env =
        Reenv.Env.make(["./test/fixtures/.env.json"])
        |> Reenv.Env.get_env("JSON");

      expect.string(env).toEqual("{\"foo\": \"bar\"}");
    },
  );

  utils.test("new lines are expanded", ({expect}) => {
    let env =
      Reenv.Env.make(["./test/fixtures/.env.new_line"])
      |> Reenv.Env.get_env("NEW_LINE");

    expect.string(env).toEqual({|new
line|});
  });
});
