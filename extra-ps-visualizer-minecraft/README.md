<div align="center">
  <img src="https://github.com/ayogun/42-project-badges/raw/main/badges/push_swapm.png" />
  <br />
  <code>Minecraft push_swap visualizer</code>
  <p>A program to flex on your friends by visualizing your push_swap algorithm in Minecraft. It uses <a src="https://valence.rs/">Valence</a> to control the game packets and visualize the sorting algorithm on your <code>1.20.1</code> client.</p>
</div>

## Demo

![In-game screenshot](/.github/assets/screenshot_1.webp)

### `--help` screen

```
Usage: mc_push_swap [OPTIONS]

Options:
  -e, --executable <EXECUTABLE>    Push_swap executable path [default: push_swap]
  -m, --makefile <MAKEFILE>        Optional Makefile path If not provided, and the executable is not found in the current working directory, the program will try to build it using the Makefile in the current working directory [default: Makefile]
  -i, --info                       Display information and settings about the program and exit
      --cwd <CWD>                  Current working directory [env: CWD=] [default: .]
      --array-size <ARRAY_SIZE>    Number of numbers to generate [env: ARRAY_SIZE=] [default: 100]
      --instr-delay <INSTR_DELAY>  Delay between each instruction [env: INSTR_DELAY=] [default: 0.01]
      --max-height <MAX_HEIGHT>    Max length of display line. Changing this will probably break the display [env: MAX_HEIGHT=] [default: 50]
  -h, --help                       Print help
  -V, --version                    Print version
```

### `--info` screen

```
INFO  mc_push_swap > -------------- Executable info --------------
INFO  mc_push_swap > Server version   : 0.1.0
INFO  mc_push_swap > Server build     : dev-build
INFO  mc_push_swap > --------------- Server config ---------------
INFO  mc_push_swap > MAX_HEIGHT : 50
INFO  mc_push_swap > ARRAY_SIZE : 100
INFO  mc_push_swap > INSTR_DELAY: 0.01
INFO  mc_push_swap > VIEW_DIST  : 10
INFO  mc_push_swap > ---------------------------------------------
```

## Usage

Run the server in the same directory as your compiled `push_swap` binary.

## Notes and gotchas

- You can either compile the binary and then run it or run it in debug mode (see
  below)
- **You probably should set the `RUST_LOG` env var to `info` when running the
  server.**
  - To do that preface your commands with `RUST_LOG=info` or run
    `export RUST_LOG=info` once
- This project will probbaly react badly to a crashing `push_swap`.
- Even if the operations are bad, as long as `push_swap` doesn't crash, the
  display should work (maybe)
- This project is not optimized or fast, neither is the code of quality.
- The server is compiled for support of paid clients only. You can edit the code
  to allow "cracked" user as well.
- If you want to contribute, DM me, find me at 42 Lyon (`elagouch`) or open an
  Issue/PR here. Thank you :-)

## Build

```sh
cargo b --release
```

## Run

```sh
cargo r --
```

## Test

```sh
cargo t
```
