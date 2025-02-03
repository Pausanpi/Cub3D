/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:49:27 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/03 10:46:29 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

#define MINIMAP_SIZE 200
#define TILE_SIZE (HEIGHT / 50)
#define MINIMAP_OFFSET 20

// Function prototype for ft_fill_square
void ft_fill_square(uint32_t color, mlx_image_t *image, int x, int y)
{
    int len_x;
	int len_y;

	len_x = x + HEIGHT / 50;
	len_y = y + HEIGHT / 50;
	while (y <= len_y)
	{
		x = len_x - HEIGHT / 50;
		while (x <= len_x)
			mlx_put_pixel(image, x++, y, color);
		y++;
	}
}

void	ft_draw_player(t_data *data, mlx_image_t *player_img, int x, int y)
{
	int	len_x;
	int	len_y;
	
	len_x = x + (HEIGHT / 50 / 2);
	len_y = y + (HEIGHT / 50 / 2);
	(void)data;
	while (++y < len_y)
	{
		x = len_x - (HEIGHT / 50 / 2);
		while (++x < len_x)
			mlx_put_pixel(player_img, x, y, RED);
	}
}

void	ft_fill_minimap(t_data *data, mlx_image_t *minimap)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == '1')
				ft_fill_square(BLACK, minimap,
					j * HEIGHT / 50, i * HEIGHT / 50);
			else if (data->map[i][j] == ' ')
				ft_fill_square(GRAY, minimap,
					j * HEIGHT / 50, i * HEIGHT / 50);
			else
				ft_fill_square(WHITE, minimap,
					j * HEIGHT / 50, i * HEIGHT / 50);
		}
	}
}

void	ft_center_minimap(mlx_image_t *minimap, mlx_image_t *player)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (player->instances[0].x + x < HEIGHT / 20)
		x++;
	while (player->instances[0].x + x > HEIGHT / 20)
		x--;
	while (player->instances[0].y + y < HEIGHT / 20)
		y++;
	while (player->instances[0].y + y > HEIGHT / 20)
		y--;
	player->instances[0].x += x + HEIGHT / 50;
	player->instances[0].y += y + HEIGHT / 50;
	minimap->instances[0].x += x + HEIGHT / 50;
	minimap->instances[0].y += y + HEIGHT / 50;
}

void	ft_draw_minimap(t_data *data)
{
	// Crear y almacenar las imágenes en t_data
	data->minimap = mlx_new_image(data->mlx, data->width_map * HEIGHT / 25, data->height_map * HEIGHT / 25);
	data->player_img = mlx_new_image(data->mlx, HEIGHT / 50 * 2, HEIGHT / 50 * 2);

	// Dibujar el minimapa y el jugador
	ft_fill_minimap(data, data->minimap);
	ft_draw_player(data, data->player_img, HEIGHT / 50 - (HEIGHT / 50 / 4), HEIGHT / 50 - (HEIGHT / 50 / 4));

	// Agregar imágenes a la ventana
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	mlx_image_to_window(data->mlx, data->player_img,
		(int)(data->player->pos->x - 1) * HEIGHT / 50, 
		(int)(data->player->pos->y - 1) * HEIGHT / 50);

	// Centrar el minimapa inicialmente
	ft_center_minimap(data->minimap, data->player_img);
}
