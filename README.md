*This project has been created as part of the 42 curriculum by <your_login>.*

# cub3D

## Description

**cub3D** is a first-person "raycasting" engine directly inspired by
*Wolfenstein 3D* (id Software, 1992), the game that started the FPS genre.
The goal of the project is to render, in real time and from a first-person
point of view, a 3D-looking view of a 2D maze described in a simple text
scene file.

The rendering is entirely computed by hand using the raycasting technique:
for each column of the screen, a ray is cast from the player's position in
the direction of the camera, and the distance at which that ray hits a wall
determines the height of the wall slice drawn on screen (the closer the
wall, the taller the slice). This project only covers the **mandatory
part** of the subject — no bonus feature is implemented.

Main goals of the project:

- Practice rigorous C programming (Norm-compliant, no leaks, no crashes).
- Discover and implement the raycasting algorithm (DDA).
- Get familiar with a graphics library (MiniLibX): windows, images, colors,
  keyboard events.
- Parse and validate a custom scene-description file format.

## Features (mandatory part)

- Real-time 3D rendering of a 2D maze from a first-person perspective,
  using raycasting.
- Window management through **MiniLibX**, smooth even when switching
  windows, minimizing, etc.
- Different wall textures depending on the side hit by the ray (North,
  South, East, West).
- Configurable floor and ceiling colors.
- Player movement (`W`, `A`, `S`, `D`) and camera rotation (`←` / `→`
  arrow keys).
- Clean exit on `ESC` or when clicking the window's red cross (no leaks,
  no crash).
- Full parsing and validation of the `.cub` scene file:
  - texture paths (`NO`, `SO`, `WE`, `EA`)
  - floor (`F`) and ceiling (`C`) colors in RGB
  - a map made of `0` (empty space), `1` (wall) and exactly one player
    start position/orientation (`N`, `S`, `E`, `W`)
  - map closed/surrounded by walls
  - any misconfiguration is reported with `Error\n` followed by an
    explicit message, and the program exits cleanly.

## Instructions

### Requirements

- A C compiler (`cc`) and `make`.
- **MiniLibX** (either the version installed on the system, or built from
  its sources).
- On Linux, the X11 development libraries required by MiniLibX
  (e.g. `libxext-dev`, `libbsd-dev`, depending on the distribution).

### Compilation

```sh
make
```

Available Makefile rules:

| Rule      | Effect                                             |
|-----------|-----------------------------------------------------|
| `all`     | Builds the `cub3D` executable                       |
| `clean`   | Removes object files                                 |
| `fclean`  | Removes object files and the executable              |
| `re`      | `fclean` followed by `all`                           |

### Execution

```sh
./cub3D path_to/map.cub
```

The program takes a single argument: a scene description file with the
`.cub` extension.

### Controls

| Key             | Action                          |
|-----------------|----------------------------------|
| `W`             | Move forward                     |
| `S`             | Move backward                    |
| `A`             | Strafe left                      |
| `D`             | Strafe right                     |
| `←` / `→`       | Look left / right                |
| `ESC`           | Quit cleanly                     |
| Window's red X  | Quit cleanly                     |

### `.cub` scene file format

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

- `NO` / `SO` / `WE` / `EA`: path to the wall texture used when a ray hits
  a north/south/west/east-facing wall.
- `F`: floor color as `R,G,B` (each value in `[0,255]`).
- `C`: ceiling color as `R,G,B` (each value in `[0,255]`).
- Map: `0` empty space, `1` wall, one of `N`/`S`/`E`/`W` for the player's
  starting position and orientation. The map must always be the last
  element of the file, must be closed by walls, and is parsed exactly as
  it appears (spaces included).

Any malformed file (missing/invalid element, unclosed map, invalid
character, etc.) makes the program print `Error\n` followed by an explicit
error message, and exit cleanly without leaking memory.

## Resources

- Lode Vandevenne, *Lode's Computer Graphics Tutorial — Raycasting*:
  https://lodev.org/cgtutor/raycasting.html (reference article for the DDA
  raycasting algorithm used in this project).
- 42 MiniLibX documentation / man pages (`mlx_init`, `mlx_new_window`,
  `mlx_put_image_to_window`, `mlx_pixel_put`, `mlx_loop`, `mlx_hook`,
  `mlx_key_hook`, `mlx_xpm_file_to_image`).
- `man` pages: `open`, `read`, `write`, `close`, `malloc`, `free`, `printf`,
  `perror`, `strerror`, `exit`, `gettimeofday`, `man 3 math`.

**AI usage:**
- Create this README.md.
- Explaination of texture mapping.