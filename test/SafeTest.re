open TestFramework;

describe("Safe functionality", utils => {
  let checkIfSafe = Reenv.checkSafe(~safeFile="./test/fixtures/.env");

  utils.test("Should raise if not all keys are there", ({expect}) =>
    expect.fn(() => checkIfSafe([])).toThrowException(
      Reenv.Missing_keys("TEST, TEST2, TEST3"),
    )
  );

  utils.test("is fine when all the keys are provided", ({expect}) =>
    expect.same(checkIfSafe(["./test/fixtures/.env"]), ())
  );
});
