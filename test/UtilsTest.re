open TestFramework;

describe("utils", utils => {
  utils.test(
    "readUntilEndOfFile - should read all lines corectly", ({expect}) => {
    let file = open_in_bin("./test/fixtures/.env");
    let rows = Reenv.Util.readUntilEndOfFile(file);

    expect.list(rows).toEqual([
      {|TEST="hello world!"|},
      {|TEST2=hello world?|},
      {|TEST3="hello=world"|},
    ]);
  });

  utils.test("escapeEquals works as expected", ({expect}) => {
    let (key, value) = Reenv.Util.escapeEquals(["test", "test", "test"]);
    expect.string(key).toEqual("test");
    expect.string(value).toEqual("test=test");
  });
});
