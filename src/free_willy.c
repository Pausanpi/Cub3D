/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_willy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:05:50 by lcuevas-          #+#    #+#             */
/*   Updated: 2025/02/13 10:40:38 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	ft_error(int i, t_data *data)
{
	ft_putstr_fd("ERROR", 2);
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	free(data->ceiling);
	free(data->floor);
	free(data->player->pos);
	free(data->player);
	free(data->ray);
	exit(i);
}

void	ft_exit(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	mlx_delete_texture(data->no);
	mlx_delete_texture(data->so);
	mlx_delete_texture(data->ea);
	mlx_delete_texture(data->we);
	free(data->ceiling);
	free(data->floor);
	free(data->player->pos);
	free(data->player);
	free(data->ray);
	free_doble(data->map);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	exit(0);
}

void	free_doble(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
