<h1>
	<img src="assets/3ds.svg" with="24" height="24" alt="3DS Icon" />
	cub3d 3DS Port
</h1>

> Native Nintendo 3DS port of the `cub3d` ray casting engine

## Implementation Details

- **MLX Shim**: A lightweight MiniLibX translation layer (`3ds/mlx_3ds.c`) that
  maps MLX calls to `libctru` framebuffers.
- **Coordinate Mapping**: Handles the 3DS's physical portrait-to-landscape
  rotation (240x400 -> 400x240) via coordinate transformation in the
  pixel-writing loop.
- **ROMFS**: All assets (maps, textures) are bundled into the `.3dsx` via ROMFS.
  Path resolution was updated to support the `romfs:/` prefix.
- **XPM Parser**: Custom XPM loader to handle textures without X11 dependencies.
- **Input**: 3DS HID (D-Pad, L/R, Buttons) mapped to standard game keycodes.
- **Debug**: Dual-screen setup with the bottom screen acting as a diagnostic
  console.

## Build Instructions

### Set up DevKitARM/DevKitPRO

DevKitARM is a suite of home-made compilers, linkers, and presets for building
targets for the Nintendo systems. Conveniently, it also contains a CMake
toolchain for the 3DS, that we're going to use.

<table>
	<tr>
<th>With Nix</th>
<th>Without Nix</th>
</tr>
	<tr>
		<td>
You must run CMake in the <code>threeDS</code> nix shell to get the
<b>DevKitARM</b> toolchain and build the homebrew. Run
<code>nix develop .#threeDS</code> at the repo root to get in the shell, and run
the build commands of the next section inside. The shell uses
<a href="https://github.com/bandithedoge/devkitNix">devkitNix</a>, which
extracts the Docker images and patches the binaries. It  may take a while to
load.
</td>
<td>
If you don't have Nix, head over to https://devkitpro.org/wiki/devkitARM for
instructions on installing <b>DevKitARM</b>/<b>DevKitPRO</b>. The environment
variables <code>DEVKITARM</code> and <code>DEVKITRO</code>, referring to the
paths, must be set in your current shell environment.
</td>
	</tr>
</table>

In the same way as other projects in this repo, you must have CMake installed to
build the homebrew, and I recommend [Ninja](https://ninja-build.org/) as the
builder. If you are running from the Nix dev shell, you already have CMake and
Ninja.

### Build the Homebrew

```bash
# Prepare the build directory
# (run this from the repository root)
# (if you don't have/want Ninja, drop the `-G Ninja` params)
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/cmake/3DS.cmake
# Build the bomebrew
cmake --build build/ --target cub3d
# This output 'cub3d.3dsx' (and other files) in 'build/milestone-4/cub3d/'.
```

### Emulation

You can run the Homebrew with your preferred emulator. I recommended[^1]
[Azahar](https://azahar-emu.org/).

```bash
azahar build/milestone-4/cub3d/cub3d.3dsx
# Or with 'nix run'
nix run nixpkgs#azahar -- build/milestone-4/cub3d/cub3d.3dsx
```

## Controls

- **D-Pad / Circle Pad / ABXY**: Movement & Rotation
- **L / R**: Strafe
- **START**: Exit (to The Homebrew Channel)

[^1]: https://azahar-emu.org/blog/game-loading-changes/
