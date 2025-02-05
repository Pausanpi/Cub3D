/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:47:47 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/05 12:23:14 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	key_hook2(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player->pos->x += cos(data->player->angle + PI / 2) * 0.05;
		data->player->pos->y += sin(data->player->angle + PI / 2) * 0.05;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player->pos->x += cos(data->player->angle - PI / 2) * 0.05;
		data->player->pos->y += sin(data->player->angle - PI / 2) * 0.05;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->angle += 0.05;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->angle -= 0.05;
}

void	key_hook(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(data->mlx, data->img);
		mlx_terminate(data->mlx);
		exit(0);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->player->pos->x += cos(data->player->angle) * 0.05;
		data->player->pos->y += sin(data->player->angle) * 0.05;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player->pos->x -= cos(data->player->angle) * 0.05;
		data->player->pos->y -= sin(data->player->angle) * 0.05;
	}
	key_hook2(data);
}
