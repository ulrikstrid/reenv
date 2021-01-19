let skip_empty_lines () =
  let file = open_in_bin "./test/fixtures/.env.with_empty_line" in
  let rows = Reenv.Util.readUntilEndOfFile file in
  Alcotest.(check int) "will find 2 rows" 2 (List.length rows)

let skip_comments () =
  let file = open_in_bin "./test/fixtures/.env.with_comment" in
  let rows = Reenv.Util.readUntilEndOfFile file in
  Alcotest.(check int) "will find 2 rows" 2 (List.length rows)

let ignore_citation_mark () =
  let env =
    Reenv.Env.make [ "./test/fixtures/.env.quotes" ]
    |> Reenv.Env.get_env "BASIC"
  in
  Alcotest.(check string) "removes quotes" "basic" env

let handle_empty_value () =
  let env =
    Reenv.Env.make [ "./test/fixtures/.env.empty" ] |> Reenv.Env.get_env "EMPTY"
  in
  Alcotest.(check string) "empty string" "" env

let handle_single_quote () =
  let env =
    Reenv.Env.make [ "./test/fixtures/.env.single_quotes" ]
    |> Reenv.Env.get_env "SINGLE_QUOTE"
  in
  Alcotest.(check string) "handle single quote" "quoted" env

let trim_whitespace () =
  let env =
    Reenv.Env.make [ "./test/fixtures/.env.trim" ] |> Reenv.Env.get_env "TRIM"
  in
  Alcotest.(check string) "trims row" "trim" env

let handle_json_env () =
  let env =
    Reenv.Env.make [ "./test/fixtures/.env.json" ] |> Reenv.Env.get_env "JSON"
  in
  Alcotest.(check string) "parses JSON correctly" "{\"foo\": \"bar\"}" env

let handle_newline () =
  let env =
    Reenv.Env.make [ "./test/fixtures/.env.new_line" ] |> Reenv.Env.get_env "NEW_LINE"
  in
  Alcotest.(check string) "expands \\n" {|new
line|} env

let s, _ =
  Junit_alcotest.run_and_report ~package:"reenv" "DotenvCompliance"
    [
      ( "DotenvCompliance",
        [
          Alcotest.test_case "empty lines are skipped" `Quick skip_empty_lines;
          Alcotest.test_case "comments are skipped" `Quick skip_comments;
          Alcotest.test_case "BASIC=basic is same as BASIC=\"basic\"" `Quick
            ignore_citation_mark;
          Alcotest.test_case
            "empty values become empty strings (EMPTY= becomes EMPTY=\"\")"
            `Quick handle_empty_value;
          Alcotest.test_case
            "single and double quoted values are escaped \
             (SINGLE_QUOTE='quoted' == SINGLE_QUOTE=\"quoted\")"
            `Quick handle_single_quote;
          Alcotest.test_case "whitespace is removed from both ends of the value"
            `Quick trim_whitespace;
          Alcotest.test_case
            "inner quotes are maintained (eg. JSON) (JSON={\"foo\": \"bar\"} \
             becomes {JSON:\"{\\\"foo\\\": \\\"bar\\\"}\")"
            `Quick handle_json_env;
          Alcotest.test_case
            "new lines are expanded"
            `Quick handle_newline;
        ] );
    ]

let suite = s

