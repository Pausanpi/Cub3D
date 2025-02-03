/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:52:27 by pausanch          #+#    #+#             */
/*   Updated: 2025/01/30 10:52:34 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	ft_traverse_map(t_data *data, int map_x, int map_y)
{
	while (map_y > 0 && map_y < data->height_map
		&& map_x > 0 && map_x < data->width_map
		&& (data->map[map_y][map_x] == '0'
		|| data->map[map_y][map_x] == 'N' || data->map[map_y][map_x] == 'S'
		|| data->map[map_y][map_x] == 'E' || data->map[map_y][map_x] == 'W'))
	{
		if (fabs(data->ray->first_x) < fabs(data->ray->first_y))
		{
			data->ray->length = data->ray->first_x;
			data->ray->first_x += data->ray->delta_x;
			map_x += data->ray->x_sign;
			data->ray->last_cross = 0;
		}
		else
		{
			data->ray->length = data->ray->first_y;
			data->ray->first_y += data->ray->delta_y;
			map_y += data->ray->y_sign;
			data->ray->last_cross = 1;
		}
	}
}

void	ft_ray_direction(t_data *data)
{
	data->ray->x_sign = 1;
	data->ray->y_sign = 1;
	if (data->ray->dir.x < 0)
		data->ray->x_sign = -1;
	if (data->ray->dir.y < 0)
		data->ray->y_sign = -1;
	if (data->ray->origin.x == (int)data->ray->origin.x)
		data->ray->origin.x += 0.0001;
	if (data->ray->origin.y == (int)data->ray->origin.y)
		data->ray->origin.y += 0.0001;
	data->ray->first_x = (ceil(data->ray->origin.x) - data->ray->origin.x)
		* data->ray->delta_x;
	if (data->ray->dir.x < 0)
		data->ray->first_x = (data->ray->origin.x - floor(data->ray->origin.x))
			* data->ray->delta_x;
	data->ray->first_y = (data->ray->origin.y - floor(data->ray->origin.y))
		* data->ray->delta_y;
	if (data->ray->dir.y > 0)
		data->ray->first_y = (ceil(data->ray->origin.y) - data->ray->origin.y)
			* data->ray->delta_y;
}

void	ft_init_ray(t_data *data, int i)
{
	double	unitary_screen_center;

	unitary_screen_center = ((i - WIDTH / 2.0) / (WIDTH / 2.0));
	data->ray->deltaang = atan(unitary_screen_center * tan(PI / 4));
	data->ray->angle = data->player->angle + data->ray->deltaang;
	data->ray->dir.x = cos(data->ray->angle);
	data->ray->dir.y = sin(data->ray->angle);
	data->ray->origin = *data->player->pos;
	data->ray->delta_x = fabs(1 / data->ray->dir.x);
	data->ray->delta_y = fabs(1 / data->ray->dir.y);
}

void	ft_rayete(t_data *data, int i)
{
	int		map_x;
	int		map_y;

	map_x = (int)data->ray->origin.x;
	map_y = (int)data->ray->origin.y;
	ft_init_ray(data, i);
	ft_ray_direction(data);
	ft_traverse_map(data, (int)data->ray->origin.x, (int)data->ray->origin.y);
	data->ray->wall_collision.x = data->ray->origin.x + data->ray->length
		* data->ray->dir.x;
	data->ray->wall_collision.y = data->ray->origin.y + data->ray->length
		* data->ray->dir.y;
}
