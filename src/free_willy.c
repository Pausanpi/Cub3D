/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_willy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:05:50 by lcuevas-          #+#    #+#             */
/*   Updated: 2025/02/27 13:35:46 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	ft_error(int i, t_data *data)
{
	ft_exit(data);
	exit(i);
}

void	ft_exit2(t_data *data)
{
	if (data->ceiling)
	{
		free(data->ceiling);
	}
	if (data->floor)
	{
		free(data->floor);
		data->floor = NULL;
	}
	free(data->player->pos);
	free(data->player);
	free(data->ray);
	if (data->map)
		free_doble(data->map);
	if (data->ceiling1)
		free_doble(data->ceiling1);
	if (data->floor1)
		free_doble(data->floor1);
}

void	ft_exit(t_data *data)
{
	if (data->img && data->mlx)
		mlx_delete_image(data->mlx, data->img);
	if (data->no)
		mlx_delete_texture(data->no);
	if (data->so)
		mlx_delete_texture(data->so);
	if (data->ea)
		mlx_delete_texture(data->ea);
	if (data->we)
		mlx_delete_texture(data->we);
	ft_exit2(data);
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
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

void	free_triple(char ***str)
{
	int	i;

	i = 0;
	if (*str != NULL)
	{
		while ((*str)[i])
		{
			free((*str)[i]);
			(*str)[i] = NULL;
		}
		free(*str);
		*str = NULL;
	}
}
