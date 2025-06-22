<div align="center">
	<img src="https://github.com/ayogun/42-project-badges/raw/main/covers/cover-cub3d.png" />
</div>

## Build

### Mandatory

```sh
make
```

## Allowed functions

> open, close, read, write,
> printf, malloc, free, perror,
> strerror, exit, gettimeofday

As well as:

-   All functions of the math library (-lm man man 3 math)
-   All functions of the MinilibX

## `src/` naming convention

We take inspiration from the Doom naming convention. The files are placed in a subdir that correspond to their subject,
and are given a prefix for their subject, and a suffix for their context (mandatory, bonus, extra).

### Prefix

| Category | Directory | Prefix |
| -- | -- | -- |
| Bonus: Doors | `door_bonus` | `i_` |
| Bonus: Minimap | `minimap_bonus` | `n_` |
| Bonus: Mouse control  | `mouse_bonus` | `o_` |
| Drawing  | `draw` | `d_` |
| Extra: FPS counter  | `fps_extra` | `f_` |
| Memory  | `memory` | `m_` |
| Parsing  | `parsing` | `p_` |
| Player  | `player` | `l_` |
| Ray casting | `raycasting` | `r_` |
| Texture  | `texture` | `t_` |
| Utilities | `utils` | `u_` |

### Suffix

| Context | Suffix |
| -- | -- |
| Mandatory | `_m` |
| Bonus | `_b` |
| Extra | `_e` |

## Inspiration

**This project was inspired by these awesome videos !** They helped us understand the many concepts of graphical 2.5D and 3D rendering, so check them out !
I watched all of them on the bus while going to school. They are definitely worth your time :-)

<!-- Centered video cards -->
<p align="center">
  <a href="https://www.youtube.com/watch?v=fSjc8vLMg8c"><img src=".github/assets/vid_jdh.png" width="200" /></a>
  <a href="https://www.youtube.com/watch?v=gYRrGTC7GtA"><img src=".github/assets/vid_3dsage.png" width="200" /></a>
  <a href="https://www.youtube.com/watch?v=HQYsFshbkYw"><img src=".github/assets/vid_bisqwit.png" width="200" /></a>
  <a href="https://www.youtube.com/watch?v=VxoWl8w2eTw"><img src=".github/assets/vid_scrotumdepoulpe.png" width="200" /></a>
</p>
