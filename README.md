# reenv

[![Build Status](https://strid.visualstudio.com/OSS/_apis/build/status/ulrikstrid.reenv?branchName=master)](https://strid.visualstudio.com/OSS/_build/latest?definitionId=23&branchName=master)

[dotenv-cli](https://github.com/entropitor/dotenv-cli) implementation in ReasonML. The goal is to have feature parity with [dotenv](https://github.com/motdotla/dotenv) but be implemented in Reason. If there is a feature missing please log an issue.

## Usage

`reenv [dotenv-file] [executable] [...args]`

### example

`reenv .env node index.js`

## simple benchmarks

```
Ulriks-MBP:reenv ulrik$ time reenv .env node index.js
hello
world!
hello world?
hello=world

real    0m0.082s
user    0m0.060s
sys     0m0.017s
Ulriks-MBP:reenv ulrik$ time dotenv node index.js
hello
world!
hello world?
hello=world

real    0m0.152s
user    0m0.118s
sys     0m0.031s
Ulriks-MBP:reenv ulrik$ time node index.js
undefined
undefined
undefined

real    0m0.080s
user    0m0.059s
sys     0m0.017s
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
