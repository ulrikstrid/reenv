# reenv

[![Build Status](https://strid.visualstudio.com/OSS/_apis/build/status/ulrikstrid.reenv?branchName=master)](https://strid.visualstudio.com/OSS/_build/latest?definitionId=23&branchName=master)

[dotenv-cli](https://github.com/entropitor/dotenv-cli) implementation in ReasonML. The goal is to have feature parity with [dotenv](https://github.com/motdotla/dotenv) but be implemented in Reason. If there is a feature missing please log an issue.

## Installation

reenv is available on all mainstream desktop platforms (Windows, macOS and Linux) and is installable via `npm`.

`npm install -g reenv`

## Usage

```
NAME
       reenv - Read dotenv file(s) and supply them to the program.

SYNOPSIS
       reenv [OPTION]... COMMAND [ARGS]...

ARGUMENTS
       ARGS
           Arguments passed to the command.

       COMMAND (required)
           Command to run

OPTIONS
       -e FILE, --env-file=FILE
           The .env files to read variables from.

       --help[=FMT] (default=auto)
           Show this help in format FMT. The value FMT must be one of `auto',
           `pager', `groff' or `plain'. With `auto', the format is `pager` or
           `plain' whenever the TERM env var is `dumb' or undefined.

       -s FILE, --safe=FILE
           The .env file with keys that need to be provided.

       --version
           Show version information.

EXIT STATUS
       reenv exits with the following status:

       0   on success.

       124 on command line parsing errors.

       125 on unexpected internal errors (bugs).
```

### example

`reenv -e .env -e .env.dev node index.js`

## simple benchmarks

```
Ulriks-MBP:reenv ulrik$ time dotenv -e test/.env node test/index.js
hello world!
hello world?
hello=world

real    0m0.152s
user    0m0.118s
sys     0m0.031s

Ulriks-MBP:reenv ulrik$ time reenv -e test/.env node test/index.js
hello world!
hello world?
hello=world

real    0m0.076s
user    0m0.056s
sys     0m0.015s

Ulriks-MBP:reenv ulrik$ time TEST=a TEST2=b TEST3=c node test/index.js
a
b
c

real    0m0.070s
user    0m0.053s
sys     0m0.014s
```

## Developing:

```
npm install -g esy pesy
git clone <this-repo>
esy install
esy build
```

### Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x reenv
```

### Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
