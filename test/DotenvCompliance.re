open TestFramework;

describe("dotenv compliance", utils => {
  utils.test("empty lines are skipped", ({expect}) => {
    let file = open_in_bin("./fixtures/.env.with_empty_line");
    let rows = Reenv.Util.readUntilEndOfFile(file);

    expect.int(List.length(rows)).toBe(2);
  });

  utils.test("BASIC=basic is same as BASIC=\"basic\"", ({expect}) => {
    let file = open_in_bin("./fixtures/.env.with_comment");
    let rows = Reenv.Util.readUntilEndOfFile(file);

    expect.int(List.length(rows)).toBe(2);
  });

  utils.test("BASIC=basic is same as BASIC=\"basic\"", ({expect}) => {
    let env =
      open_in_bin("./fixtures/.env.quotes")
      |> Reenv.t_of_in_channel(Reenv.make())
      |> Reenv.get_exn("BASIC");

    expect.string(env).toEqual("basic");
  });

  utils.test(
    "empty values become empty strings (EMPTY= becomes EMPTY=\"\")",
    ({expect}) => {
    let env =
      open_in_bin("./fixtures/.env.empty")
      |> Reenv.t_of_in_channel(Reenv.make())
      |> Reenv.get_exn("EMPTY");

    expect.string(env).toEqual("");
  });

  utils.test(
    "single and double quoted values are escaped (SINGLE_QUOTE='quoted' == SINGLE_QUOTE=\"quoted\")",
    ({expect}) => {
      let env =
        open_in_bin("./fixtures/.env.single_quotes")
        |> Reenv.t_of_in_channel(Reenv.make())
        |> Reenv.get_exn("SINGLE_QUOTE");

      expect.string(env).toEqual("quoted");
    },
  );

  utils.test("whitespace is removed from both ends of the value", ({expect}) => {
    let env =
      open_in_bin("./fixtures/.env.trim")
      |> Reenv.t_of_in_channel(Reenv.make())
      |> Reenv.get_exn("TRIM");

    expect.string(env).toEqual("trim");
  });

  utils.test(
    "inner quotes are maintained (think JSON) (JSON={\"foo\": \"bar\"} becomes {JSON:\"{\\\"foo\\\": \\\"bar\\\"}\")",
    ({expect}) => {
      let env =
        open_in_bin("./fixtures/.env.json")
        |> Reenv.t_of_in_channel(Reenv.make())
        |> Reenv.array_of_t;

      let first = env[0];

      expect.string(first).toEqual("JSON={\"foo\": \"bar\"}");
    },
  );

  utils.test("new lines are expanded", ({expect}) => {
    let env =
      open_in_bin("./fixtures/.env.new_line")
      |> Reenv.t_of_in_channel(Reenv.make())
      |> Reenv.array_of_t;

    let first = env[0];

    expect.string(first).toEqual({|NEW_LINE=new
line|});
  });
});
