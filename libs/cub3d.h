/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:33:38 by lcuevas-          #+#    #+#             */
/*   Updated: 2025/02/05 14:16:55 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*---------------------------------   LIBS   ---------------------------------*/
# include "libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include <fcntl.h>
# include <limits.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <memory.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*--------------------------------   MACROS   --------------------------------*/
/*SIZE*/
# define WIDTH 1080
# define HEIGHT 700
// esto copiadito de la elisa
# define WALL_H 600 // altura del muro, puse eso por probar xd
# define WALL_W 500 // ancho del muro, puse eso por probar xd
# define FOV 90 // campo de visión. YO lo tengo en radianes. Deber\oia ser PI/2
//ERORS
# define MLX_ERROR 1
# define IMG_ERROR 2
/*PI*/
# define PI 3.14159265358979323846 //existe el M_PI pero me puedo fiar?
/*MARGEN DE ERROR*/
# define EPSILON 0.3 //no era el margen de error, si yo sabia





# define BLACK 0x000000ff
# define WHITE 0xffffffff
# define RED 0xff0000ff
# define GRAY 0x808080ff
# define BLUE 0x0000ffff
# define PINK 0xF8A4A7ff
# define TRANSPARENT 0x00000000
/*--------------------------------   STRUCTS   -------------------------------*/

typedef struct s_paint
{
	int		top;
	int		bot;
	float	tex_x;
	float	tex_y;
	float	step;
	mlx_texture_t *current_texture;
	uint8_t	*pixel;
} t_paint;

typedef struct s_rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

typedef struct s_coordinate
{
	double	x; //como lo calculo esto ser'ia la magnitud del rayo por undiad de x
	double	y; //lo mismo con y
}	t_coordinate;

typedef struct s_player
{
	t_coordinate	*pos;
	t_coordinate	*center;
	mlx_image_t		*player_img;
	mlx_image_t		*line_img;
	mlx_t			*mlx;
	int				color;
	double			angle; //esta en radianes ya directo. con int podria ser grados ccreo
	int				size;
}	t_player;

typedef struct s_collision       // NO HACE FALTA HASTA EL BONUS
{
	t_coordinate	coordinate;
	double			hypotenuse;
	// eli marca una distancia, que quiza sea pa evitar el ojo de pez
}	t_collision;

typedef struct s_ray
{
	double			angle;
	double			deltaang;
	t_coordinate	origin;
	t_coordinate	dir;
	double			delta_x; //this is the absolute distance that the ray has to traverse for a collision with the grid.
	double			delta_y;
	double			first_x;
	double			first_y;
	double			length;
	int				x_sign; // initiate at 1 and then if chage to -1 to fix direction
	int				y_sign;
	int				last_cross; //0 si toco x, 1 si toco y. Asi se puede restar el ultimo paso
	t_coordinate	wall_collision;
	int				map_x;
	int				map_y;
}	t_ray;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_ray			*ray;
	t_player		*player;	
	char			**map;
	int				fd;
	char			*line;
	int				texture_count;
	int				char_pos;
	char			orientation;
	int				height_map;
	int				width_map;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	uint32_t		*ceiling;
	uint32_t		*floor;

	mlx_image_t		*minimap;
	mlx_image_t		*player_img;

	int			prueba;
}	t_data;

/*-------------------------------   FUNCTIONS   ------------------------------*/

// main
int		main(int argc, char **argv);

// raycast
void	ft_rayete(t_data *data, int i);
void	ft_traverse_map(t_data *data, int map_x, int map_y);
void	ft_ray_direction(t_data *data);
void	ft_init_ray(t_data *data, int i);

// map_checker
int		check_textures(t_data *data, char **texture);
int		save_map(t_data *data);
int		check_map(t_data *data);
int		check_chars(t_data *data);
int		fill_map(t_data *data);

// utils_map_check
void	gnl_texture(t_data *data, char **texture);
char	*gnl_ft_strjoin2(char *s1, char *s2);
int		check_first_line(t_data *data);
int		ft_bucle(t_data *data, int i, int j);

// parse
int		parser(t_data *data, char *file);

// textures
int		load_textures(t_data *data, char *textures);

// utils
void	ft_error(int i, t_data *data);
void	free_doble(char **str);
void	print_error(char *str);
int		save_texture_wall(t_data *data, char **path_text_walls);

// keys
void		key_hook(t_data *data);
void	key_hook2(t_data *data);

// draw
void	ft_paint_walls(t_data *f, float wall, int col);

// init
void	init_struct(t_data *data);
void	init_mlx(t_data *data);
void	ft_init_pos(t_data *data);

#endif
