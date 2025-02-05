/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:08:24 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/05 12:24:28 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

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

	float wall_x;
	if (f->ray->last_cross == 0)
		wall_x = f->ray->wall_collision.y - floor(f->ray->wall_collision.y);
	else
		wall_x = f->ray->wall_collision.x - floor(f->ray->wall_collision.x);

	if (f->ray->last_cross == 0)
	{
		if (f->ray->x_sign == 1)
			current_texture = f->we;
		else
			current_texture = f->ea;
	}
	else
	{
		if (f->ray->y_sign == 1)
			current_texture = f->no;
		else
			current_texture = f->so;
	}
	tex_x = wall_x * current_texture->width;
	top = HEIGHT / 2 - wall / 2;
	if (top < 0)
		top = 0;
	bot = top + wall;
	if (bot > HEIGHT)
		bot = HEIGHT;
	step = (float)current_texture->height / wall;
	tex_y = 0;
	if (top == 0)
		tex_y = -(HEIGHT / 2 - wall / 2) * step;

	j = 0;
	while (j < HEIGHT)
	{
		if (j < top)
			mlx_put_pixel(f->img, col, j, (f->ceiling[0] << 24 | f->ceiling[1] << 16 | f->ceiling[2] << 8 | 255)); // Ceiling
		else if (j > bot)
			mlx_put_pixel(f->img, col, j, (f->floor[0] << 24 | f->floor[1] << 16 | f->floor[2] << 8 | 255)); // Floor
		else
		{
			int tex_y_int = (int)tex_y % current_texture->height;
			pixel = &current_texture->pixels[
				(tex_y_int * current_texture->width + (int)tex_x) * current_texture->bytes_per_pixel];
			uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | 255;
			mlx_put_pixel(f->img, col, j, color);
			tex_y += step;
		}
		j++;
	}
}
