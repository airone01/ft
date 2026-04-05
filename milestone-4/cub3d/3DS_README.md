# cub3d 3DS Port

Native Nintendo 3DS port of the `cub3d` raycasting engine.

## Implementation Details

- **MLX Shim**: Implemented a lightweight MiniLibX translation layer
  (`3ds/mlx_3ds.c`) that maps MLX calls to `libctru` framebuffers.
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

You must use the `threeDS` nix shell to get the `devkitARM` toolchain. I will
probably not be configuring Bazel to build the app, this script will do.

```bash
nix develop .#threeDS
cd milestone-4/cub3d/
./build_3ds.sh
```

This produces `cub3d.3dsx`.

## Controls

- **D-Pad / Circle Pad / ABXY**: Movement & Rotation
- **L / R**: Strafe
- **START**: Exit to Homebrew Menu
