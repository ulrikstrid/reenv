# reenv

Minimal dotenv-cli implementation in ReasonML.

## Usage

`reenv.exe [dotenv-file] [executable] [...args]`

### example

`reenv.exe .env node index.js`

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
esy x reenv.exe
```

### Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
