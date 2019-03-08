open TestFramework;

describe("Safe functionality", utils =>
  utils.test("1 + 1 should equal 2", ({expect}) =>
    expect.int(1 + 2).toBe(3)
  )
);
