/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:53:38 by pausanch          #+#    #+#             */
/*   Updated: 2025/01/29 17:13:38 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	ft_error(int i, t_data *data)
{
	ft_putstr_fd("ERROR", 2);
	(void)data;
	exit(i);
}

void	ft_paint_walls(t_data *f, float wall, int col)
{
	int		j;
	int		top;
	int		bot;
	float	tex_x;
	float	tex_y;
	float	step;
	mlx_texture_t *current_texture;
	uint8_t	*pixel;

	// Calcular el punto exacto donde golpea el rayo
	float wall_x;
	if (f->ray->last_cross == 0)  // Hit vertical
		wall_x = f->ray->wall_collision.y - floor(f->ray->wall_collision.y);
	else  // Hit horizontal
		wall_x = f->ray->wall_collision.x - floor(f->ray->wall_collision.x);

	// Seleccionar la textura según la orientación de la pared
	if (f->ray->last_cross == 0)
	{
		if (f->ray->x_sign == 1)
			current_texture = f->ea;
		else
			current_texture = f->we;
	}
	else
	{
		if (f->ray->y_sign == 1)
			current_texture = f->so;
		else
			current_texture = f->no;
	}

	// Calcular la coordenada x de la textura
	tex_x = wall_x * current_texture->width;

	top = HEIGHT / 2 - wall / 2;
	if (top < 0)
		top = 0;
	bot = top + wall;
	if (bot > HEIGHT)
		bot = HEIGHT;

	// Calcular el paso para mapear la textura
	step = (float)current_texture->height / wall;

	j = 0;
	while (j < HEIGHT)
	{
		if (j < top)
			mlx_put_pixel(f->img, col, j, (255 << 24 | 135 << 16 | 206 << 8 | 235)); // Cielo
		else if (j > bot)
			mlx_put_pixel(f->img, col, j, (255 << 24 | 169 << 16 | 169 << 8 | 169)); // Suelo
		else
		{
			// Mapear la coordenada y de la pantalla a la coordenada y de la textura
			tex_y = (j - top) * step;
			
			// Obtener el color del pixel de la textura
			pixel = &current_texture->pixels[
				((int)tex_y * current_texture->width + (int)tex_x) * current_texture->bytes_per_pixel];
			
			// Crear el color RGBA
			uint32_t color = (255 << 24) | (pixel[0] << 16) | (pixel[1] << 8) | pixel[2];
			
			// Aplicar sombreado basado en la distancia
			float shade = 1.0f - (f->ray->length / 20.0f); // Ajusta el 30.0f según necesites
			if (shade < 0.2f) shade = 0.2f;
			
			// Aplicar el sombreado al color
			uint8_t r = (color >> 16) & 0xFF;
			uint8_t g = (color >> 8) & 0xFF;
			uint8_t b = color & 0xFF;
			r = r * shade;
			g = g * shade;
			b = b * shade;
			
			color = (255 << 24) | (r << 16) | (g << 8) | b;
			
			mlx_put_pixel(f->img, col, j, color);
		}
		j++;
	}
}

void	ft_hook(void *param)
{
	t_data	*f;
	int		i;

	f = param;
	if (mlx_is_key_down(f->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(f->mlx);
	if (mlx_is_key_down(f->mlx, MLX_KEY_W))
		f->player->pos->x += 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_S))
		f->player->pos->x -= 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_D))
		f->player->pos->y += 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_A))
		f->player->pos->y -= 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_E))
		f->player->angle += 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_Q))
		f->player->angle -= 0.05;
	i = 0;
	while (i < 1080)
	{
		ft_rayete (f, i);
		ft_paint_walls(f, (WALL_H - (f->ray->length) * 30), i); // habia uqe añadirle datos de colision
		i += 1;
	}
}

void	ft_openwindow(t_data *f)
{
	mlx_loop_hook(f->mlx, &ft_hook, f);
	mlx_loop(f->mlx);
	mlx_delete_image(f->mlx, f->img);
	mlx_terminate(f->mlx);
}

static void init_struct(t_data *data)
{	
    data->fd = 0;
    data->line = NULL;
    data->texture_count = 0;
    data->char_pos = 0;
	data->height_map = 0;
    data->width_map = 0;

	data->player = malloc(sizeof(t_player));
	data->player->pos = malloc(sizeof(t_coordinate));
	
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx_init(WIDTH, HEIGHT, "VENTANA", false);
	if (!data->mlx)
		ft_error(MLX_ERROR, data);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->player->angle = 0;
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(IMG_ERROR, data);

	data->ray = malloc(sizeof(t_ray));
	
	data->no = malloc(sizeof(mlx_texture_t));
	data->so = malloc(sizeof(mlx_texture_t));
	data->ea = malloc(sizeof(mlx_texture_t));
	data->we = malloc(sizeof(mlx_texture_t));
}

static int check_extension(char *file)
{
    int i;

    i = 0;
    while (file[i])
        i++;
    if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i - 4] != '.')
        return (1);
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
        return (printf("Error: Invalid number of arguments\n"), 1);
    if (check_extension(argv[1]) == 1)
        return (printf("Error: Invalid file extension\n"), 1);
    init_struct(&data);
    if (parser(&data, argv[1]) == 1)
	{
        return (1);
	}

/* 	int i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	} */

	ft_openwindow(&data);
	return (0);
}