/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:06:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/01/30 11:16:56 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

int color_check(t_data data, char **text_walls)
{
	int i;
	int j;
	char *color;
	
	i = 3;

	while (text_walls[i])
	{
		if (ft_strncmp(text_walls[i], "F ", 2))
			data.floor = text_walls[i];
		else if (ft_strncmp(text_walls[i], "C ", 2))
			data.ceiling = text_walls[i];
		else
			return (1);
		i++;
	}
	return (0);
}

void load_textures(t_data *data, char *textures)
{
	char **text_walls;
	char **path_text_walls;
	int i;
	int j;

	text_walls = ft_split(textures, '\n');

	path_text_walls = malloc(sizeof(char *) * 4);
	i = 0;
	while (i <= 3)
	{
		path_text_walls[i] = malloc(sizeof(char) * 100);
		j = 3;
		while (text_walls[i][j])
		{
			path_text_walls[i][j - 3] = text_walls[i][j];
			j++;
		}
		path_text_walls[i][j - 3] = '\0';
		i++;
	}
	data->no = mlx_load_png(path_text_walls[0]);
	data->so = mlx_load_png(path_text_walls[1]);
	data->ea = mlx_load_png(path_text_walls[2]);
	data->we = mlx_load_png(path_text_walls[3]);
}
