/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:27:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/05 12:31:45 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

//arreglar
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

void	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

static int	check_ext_wall(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (path[i - 1] != 'g' || path[i - 2] != 'n'
		|| path[i - 3] != 'p' || path[i - 4] != '.')
		return (1);
	return (0);
}

int	save_texture_wall(t_data *data, char **path_text_walls)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path_text_walls[i] && i < 4)
	{
		if (check_ext_wall(path_text_walls[i]))
			return (print_error("Incorrect path texture"), 1);
		i++;
	}
	data->no = mlx_load_png(path_text_walls[0]);
	data->so = mlx_load_png(path_text_walls[1]);
	data->ea = mlx_load_png(path_text_walls[2]);
	data->we = mlx_load_png(path_text_walls[3]);
	return (0);
}
