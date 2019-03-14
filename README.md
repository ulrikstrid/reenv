# reenv

[![Build Status](https://strid.visualstudio.com/OSS/_apis/build/status/ulrikstrid.reenv?branchName=master)](https://strid.visualstudio.com/OSS/_build/latest?definitionId=23&branchName=master)

[dotenv-cli](https://github.com/entropitor/dotenv-cli) implementation in native ReasonML. The goal is to have feature parity with [dotenv](https://github.com/motdotla/dotenv) but be implemented in Reason. If there is a feature missing please log an issue.

reenv is compiled as a binary and there is no node involved when running it as you can see in the [benchmarks section](#simple-benchmarks).

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
Ulriks-MBP:reenv ulrik$ time TEST=hello printenv TEST
hello

real	0m0.004s
user	0m0.001s
sys	0m0.003s
Ulriks-MBP:reenv ulrik$ time reenv -e test/fixtures/.env printenv TEST
hello world!

real	0m0.008s
user	0m0.003s
sys	0m0.003s
Ulriks-MBP:reenv ulrik$ time dotenv -e test/fixtures/.env printenv TEST
hello world!

real	0m0.088s
user	0m0.067s
sys	0m0.018s
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
