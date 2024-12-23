<p align="center">
  <img src="so_long.gif"/>
</p>

<h1 align="center">so_long</h1>
<h2 align="center">42 School Project</h2>

<p align="center">
  <b>so_long</b> is a beginner-level graphical game built as part of the curriculum at <b>ecole 42</b>. It is developed using the <b>MiniLibX</b> (MLX) framework, which provides an interface to work with windows, images, and events in a simple way. The game involves moving a character through a maze, collecting items, and reaching the exit.
</p>

## Table of Contents
- [Introduction](#introduction)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Makefile](#makefile)
- [MiniLibX](#minilibx)

## Introduction
In **so_long**, the player navigates a simple 2D maze, collecting items and avoiding obstacles. The goal is to collect all the items and reach the exit to win the game. This project helps introduce graphical programming concepts while reinforcing knowledge of C and error handling.

## Requirements
To compile and run this project, you will need:
- **Linux or macOS** environment
- **MiniLibX (MLX)** library installed
- **gcc** (or similar compiler)
- **X11 libraries** (for Linux users)
- **OpenGL and AppKit frameworks** (for macOS users)

## Installation
Clone the repository :
```bash
git clone https://github.com/aria-vero-s/so_long.git
```

## Usage
After cloning the repository, you can compile and run the project with the provided Makefile.

### Compiling the Program
```bash
make
```

This will generate the `so_long` executable.

### Running the Game
```bash
./so_long <map_file.ber>
```

example:
```bash
./so_long <maps/map_valid.ber>
```

You need to provide a valid `.ber` map file for the game to load (view existing maps in the maps folder or create your own). The map should follow a specific structure, which will be documented later.

## Makefile
The Makefile is designed to simplify the compilation process. Here are the main rules:

- **`make`**: Compiles the project into the executable.
- **`make clean`**: Removes object files.
- **`make fclean`**: Removes object files and the executable.
- **`make re`**: Cleans and recompiles the project.

### How the Makefile Works
- The `all` rule compiles the project and links it with the necessary libraries (`libmlx`, `Xext`, and `X11`).
- The `clean` and `fclean` rules help keep your workspace clean by removing object files and executables, respectively.
- The `re` rule recompiles the project from scratch.

## MiniLibX
The  **MiniLibX** library was cloned from this repository (provided in the subject PDF).
```
git clone https://github.com/42Paris/minilibx-linux.git mlx
```

The images were found here:
- [merchant-shade.itch.io](https://merchant-shade.itch.io/16x16-mini-world-sprites)

The conversion from PNG to XML was made here:
- [convertio.co](https://convertio.co/png-xpm/)

The images were cropped here:
- [iloveimg.com](https://www.iloveimg.com/)
