/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:06:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/19 11:10:56 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	initialize_colors(t_data *data)
{
	data->ceiling = malloc(sizeof(uint32_t) * 3);
	data->floor = malloc(sizeof(uint32_t) * 3);
	if (!data->ceiling || !data->floor)
		return ;
	ft_memset(data->ceiling, 0, sizeof(uint32_t) * 3);
	ft_memset(data->floor, 0, sizeof(uint32_t) * 3);
}

int	validate_and_assign_colors(uint32_t *color_array, char **rgb)
{
	int	i;
	int	j;
	int	color_val;

	i = 0;
	while (i < 3)
	{
		if (!rgb[i])
			return (print_error("Missing RGB value"), 1);
		j = -1;
		if (!ft_isdigit(rgb[i][++j]))
			return (free(rgb), print_error("Invalid RGB value"), 1);
		color_val = ft_atoi(rgb[i]);
		if (color_val < 0 || color_val > 255)
		{
			free(rgb);
			return (print_error("Invalid RGB value"), 1);
		}
		color_array[i] = color_val;
		i++;
	}
	free_doble(rgb);
	return (0);
}

int	process_color_line(char *line, uint32_t *color_array)
{
	int		i;
	char	**rgb;

	i = 1;
	while (line[i] == ' ')
		i++;
	rgb = ft_split(line + i, ',');
	if (!rgb)
		return (1);
	if (validate_and_assign_colors(color_array, rgb))
		return (1);
	return (0);
}

int	color_check(t_data *data, char **text_walls)
{
	int	i;

	initialize_colors(data);
	i = 3;
	while (text_walls[i])
	{
		while (text_walls[i][0] == ' ')
			text_walls[i]++;
		if (text_walls[i][0] == 'C' && text_walls[i][1] == ' ')
		{
			if (process_color_line(text_walls[i], data->ceiling))
				return (1);
		}
		else if (text_walls[i][0] == 'F' && text_walls[i][1] == ' ')
		{
			if (process_color_line(text_walls[i], data->floor))
				return (1);
		}
		i++;
	}
	return (0);
}

int	load_textures(t_data *data, char *textures)
{
	int		i;
	int		j;
	char	**text_walls;
	char	**path_walls;

	text_walls = ft_split(textures, '\n');
	path_walls = malloc(sizeof(char *) * ft_strlen(textures));
	i = -1;
	while (++i <= 3)
	{
		ft_comprb(text_walls, i);
		path_walls[i] = malloc(sizeof(char) * (ft_strlen(text_walls[i]) - 2));
		j = 2;
		while (text_walls[i][++j])
			path_walls[i][j - 3] = text_walls[i][j];
		path_walls[i][j - 3] = '\0';
	}
	path_walls[i] = 0;
	if (save_texture_wall(data, path_walls))
		return (free_doble(path_walls), free_doble(text_walls), 1);
	if (color_check(data, text_walls))
		return (free_doble(path_walls), free_doble(text_walls), 1);
	return (free_doble(text_walls), free_doble(path_walls), 0);
}
