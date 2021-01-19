let read_until_end () =
  let file = open_in_bin "./test/fixtures/.env" in
  let rows = Reenv.Util.readUntilEndOfFile file in
  Alcotest.(check (list string))
    "reads all"
    [ {|TEST="hello world!"|}; {|TEST2=hello world?|}; {|TEST3="hello=world"|} ]
    rows

let escape_equals () =
  let key, value = Reenv.Util.escapeEquals [ "test"; "test"; "test" ] in
  Alcotest.(check string) "key" "test" key;
  Alcotest.(check string) "value" "test=test" value

let s, _ =
  Junit_alcotest.run_and_report ~package:"reenv" "Utils"
    [
      ( "Utils",
        [
          Alcotest.test_case
            "readUntilEndOfFile - should read all lines corectly" `Quick
            read_until_end;
          Alcotest.test_case "escapeEquals works as expected" `Quick
            escape_equals;
        ] );
    ]

let suite = s
