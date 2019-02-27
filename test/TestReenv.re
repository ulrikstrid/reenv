open TestFramework;

describe("readUntilEndOfFile", ({test}) =>
  test("should read all lines corectly", ({expect}) => {
    let file = open_in_bin("./test/.env");
    let rows = Reenv.Util.readUntilEndOfFile(file);

    expect.list(rows).toContainEqual("TEST=\"hello\\nworld!\"");
    expect.list(rows).toContainEqual("TEST2=hello world?");
    expect.list(rows).toContainEqual("TEST3=\"hello=world\"");
  })
);

TestFramework.cli();

/*
 Reenv.main(["", "./test/.env", "node", "./test/index.js"]);
 */

/*
 Rule from node implementation of dotonv

 BASIC=basic becomes {BASIC: 'basic'}
 empty lines are skipped
 lines beginning with # are treated as comments
 empty values become empty strings (EMPTY= becomes {EMPTY: ''})
 single and double quoted values are escaped (SINGLE_QUOTE='quoted' becomes {SINGLE_QUOTE: "quoted"})
 new lines are expanded if in double quotes (MULTILINE="new\nline" becomes
 inner quotes are maintained (think JSON) (JSON={"foo": "bar"} becomes {JSON:"{\"foo\": \"bar\"}")
 whitespace is removed from both ends of the value (see more on trim) (FOO=" some value " becomes {FOO: 'some value'})
 */
