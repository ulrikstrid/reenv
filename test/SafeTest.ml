let check_if_safe = Reenv.checkSafe ~safeFile:"./test/fixtures/.env"

let raise_missing_keys () =
  let test () = check_if_safe [] in
  Alcotest.check_raises "fails" (Reenv.Missing_keys "TEST, TEST2, TEST3") test

let works_if_no_missing () =
  Alcotest.(check unit) "works" () (check_if_safe [ "./test/fixtures/.env" ])

let s, _ =
  Junit_alcotest.run_and_report ~package:"reenv" "DotenvSafe"
    [
      ( "Safe functionality",
        [
          Alcotest.test_case "Should raise if not all keys are there" `Quick
            raise_missing_keys;
          Alcotest.test_case "is fine when all the keys are provided" `Quick
            works_if_no_missing;
        ] );
    ]

let suite = s
