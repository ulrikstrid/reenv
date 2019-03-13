open TestFramework;

describe("Safe functionality", utils => {
  let checkIfSafe = Reenv.checkSafe(~safeFile="./fixtures/.env");

  utils.test("Should raise if not all keys are there", ({expect}) =>
    expect.fn(() => checkIfSafe(Reenv.make())).toThrowException(
      Reenv.Missing_keys("TEST2, TEST, TEST3"),
    )
  );

  utils.test("is fine when all the keys are provided", ({expect}) => {
    let env =
      open_in_bin("./fixtures/.env") |> Reenv.t_of_in_channel(Reenv.make());

    expect.same(checkIfSafe(env), ());
  });
});
