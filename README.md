<h1>
  <img src="https://media1.tenor.com/m/PY-UvhqJ6OcAAAAd/captain-marvel-goose.gif" width="60px"> Cub3D
</h1>

<p>
  This project is inspired by the world-famous eponymous 90's game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you'll have to find your way.
</p>

<h3>Description</h3>
The goal of the project is to display a dynamic view inside a maze, with the ability to traverse the maze.

The input is a .cub file that contains the following customisable map specifications: wall textures for all directions, sprite texture(s), floor and ceiling colours/textures, and lastly, the map.

The map will be denoted as follows: 1 for wall, 0 for floor, space for void, N/S/E/W for spawn position and orientation.

<h3>Project Tree</h3>

```
.
├── MLX42/
├── libs/
|    ├─ libft/
|    └─ cub3d.h
├── maps/
├── src/
|    ├─ draw.c
|    ├─ free_willy.c
|    ├─ ft_raycast.c
|    ├─ init.c
|    ├─ keys.c
|    ├─ main.c
|    ├─ map_checker.c
|    ├─ parse.c
|    ├─ textures.c
|    ├─ utils.c
|    └─ utils_map_check.c
├── textures/
└── Makefile
```
