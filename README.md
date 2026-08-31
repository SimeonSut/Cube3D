*This project has been created as part of the 42 curriculum by <login1>[, <login2>[, <login3>[...]]].*

# cub3D - My first RayCaster with miniLibX

## Description
**cub3D** is a 3D graphical game engine designed from a first-person perspective, heavily inspired by the world-famous 1992 masterpiece *Wolfenstein 3D*. Written entirely in C, the project serves as a practical exploration of mathematics and basic algorithms, specifically utilizing the technique of **Ray-Casting** to simulate a dynamic three-dimensional view inside a maze.

The core engine parses a scene description file (`*.cub`) containing configuration variables and map layouts. It then renders a smooth, real-time window environment where wall textures dynamically shift depending on the cardinal direction they face (North, South, East, West), alongside customized floor and ceiling color palettes.

## Instructions

### Compilation
The project compiles via an included `Makefile` that handles rules cleanly without any unnecessary relinking. Run the following commands in your terminal:

*   **Compile the mandatory program:**
    ```bash
    make
    ```
*   **Compile with bonus features (if applicable):**
    ```bash
    make bonus
    ```
*   **Clean object files:**
    ```bash
    make clean
    ```
*   **Full clean (removes objects and binary):**
    ```bash
    make fclean
    ```
*   **Recompile from scratch:**
    ```bash
    make re
    ```

### Execution
To run the executable, pass a valid scene description file with the `.cub` extension as the first argument:

```bash
./cub3D maps/classic.cub
```

### Controls
*   **W, A, S, D:** Move the player's point of view through the maze.
*   **Left / Right Arrows:** Rotate the camera view left and right.
*   **ESC / Red Window Cross:** Safely and cleanly exit the program.

## Resources

### Documentation & References
*   **Lode's Computer Graphics Tutorial:** Renowned mathematical breakdown of Ray-Casting mechanics, DDA (Digital Differential Analysis) algorithms, and texture mapping principles.
*   **MiniLibX Graphical Library:** Official documentation regarding window management, color handling, image buffers, and keyboard/mouse event hooks.
*   **Wolfenstein 3D History:** Architectural analysis of John Carmack’s original 1992 rendering engine paradigms.

### AI Usage Disclaimer
Create this README file
