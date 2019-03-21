Tests.TestFramework.run(
  Rely.RunConfig.withReporters(
    [Default, JUnit("./junit.xml")],
    Rely.RunConfig.initialize(),
  ),
);
