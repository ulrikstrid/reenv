let environment = Reenv.Util.readUntilEndOfFile(open_in_bin("./test/.env"));

environment == ["TEST=\"hello world!\""];

Reenv.main(["", "./test/.env", "node", "./test/index.js"]);
