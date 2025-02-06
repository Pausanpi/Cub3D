/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:08:24 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/05 14:35:06 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

float	ft_distance(t_data *data, mlx_texture_t **current)
{
	float	wall_x;

	if (data->ray->last_cross == 0)
		wall_x = data->ray->wall_collision.y
			- floor(data->ray->wall_collision.y);
	else
		wall_x = data->ray->wall_collision.x
			- floor(data->ray->wall_collision.x);
	if (data->ray->last_cross == 0)
	{
		if (data->ray->x_sign == 1)
			*current = data->we;
		else
			*current = data->ea;
	}
	else
	{
		if (data->ray->y_sign == 1)
			*current = data->no;
		else
			*current = data->so;
	}
	return (wall_x * (*current)->width);
}

void	ft_peint(t_data *f, int col, t_paint *p, int j)
{
	int			tex_y_int;
	uint32_t	color;

	while (j < HEIGHT)
	{
		if (j < p->top)
			mlx_put_pixel(f->img, col, j, (f->ceiling[0] << 24
					| f->ceiling[1] << 16 | f->ceiling[2] << 8 | 255));
		else if (j > p->bot)
			mlx_put_pixel(f->img, col, j, (f->floor[0] << 24
					| f->floor[1] << 16 | f->floor[2] << 8 | 255));
		else
		{
			tex_y_int = (int)p->tex_y % p->current_texture->height;
			p->pixel = &p->current_texture->pixels[
				(tex_y_int * p->current_texture->width + (int)p->tex_x)
				* p->current_texture->bytes_per_pixel];
			color = (p->pixel[0] << 24)
				| (p->pixel[1] << 16) | (p->pixel[2] << 8) | 255;
			mlx_put_pixel(f->img, col, j, color);
			p->tex_y += p->step;
		}
		j++;
	}
}

void	ft_paint_walls(t_data *f, float wall, int col)
{
	t_paint	*p;
	int		j;

	j = 0;
	p = malloc(sizeof(t_paint));
//	p->current_texture = malloc(sizeof(mlx_texture_t));
	p->tex_x = ft_distance(f, &p->current_texture);
	p->top = HEIGHT / 2 - wall / 2;
	if (p->top < 0)
		p->top = 0;
	p->bot = p->top + wall;
	if (p->bot > HEIGHT)
		p->bot = HEIGHT;
	p->step = (float)p->current_texture->height / wall;
	p->tex_y = 0;
	if (p->top == 0)
		p->tex_y = -(HEIGHT / 2 - wall / 2) * p->step;
	ft_peint(f, col, p, j);
	free(p);
	//hay que liberar la estructura p
}
