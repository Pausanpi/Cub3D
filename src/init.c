/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:16:01 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/04 16:23:19 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	init_struct(t_data *data)
{
	data->fd = 0;
	data->line = NULL;
	data->texture_count = 0;
	data->char_pos = 0;
	data->height_map = 0;
	data->width_map = 0;
	data->player = malloc(sizeof(t_player));
	data->player->pos = malloc(sizeof(t_coordinate));
	data->ray = malloc(sizeof(t_ray));
	if (!data->player || !data->player->pos || !data->ray)
		ft_error(1, data);
}

void	init_mlx(t_data *data)
{
//	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUBESITO", false);
	if (!data->mlx)
		ft_error(MLX_ERROR, data);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(IMG_ERROR, data);
}

void	ft_init_pos(t_data *data)
{
	if (data->orientation == 'N')
		data->player->angle = 3 * PI / 2;
	else if (data->orientation == 'S')
		data->player->angle = PI / 2;
	else if (data->orientation == 'W')
		data->player->angle = 0;
	else if (data->orientation == 'E')
		data->player->angle = PI;
}