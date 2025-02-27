/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:48:18 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/27 14:42:02 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

int	check_textures(t_data *data, char **texture)
{
	while (data->line && data->line[0] != '1' && data->line[0] != ' ')
	{
		if (data->line[0] == '\n')
		{
			
		}
		else if ((ft_strncmp(data->line, "NO", 2) || ft_strncmp(data->line, "SO", 2)
		|| ft_strncmp(data->line, "WE", 2)
		|| ft_strncmp(data->line, "EA", 2)) && (data->line[2] == ' '
			|| (data->line[2] >= 9 && data->line[3] <= 13)))
			gnl_texture(data, texture);
		else if ((ft_strncmp(data->line, "F", 1)
		|| ft_strncmp(data->line, "C", 1)) && (data->line[1] == ' '
			|| (data->line[1] >= 9 && data->line[2] <= 13)))
			gnl_texture(data, texture);
		else if (data->line)
			data->texture_count++;
		free(data->line);
		data->line = get_next_line(data->fd);
		if (data->line && data->line[0] >= 9 && data->line[0] <= 13)
		{
			free(data->line);
			data->line = get_next_line(data->fd);
		}
	}
	if (data->texture_count < 6)
		return (free(data->line),
			print_error("Missing textures"), 1);
	else if (data->texture_count > 6)
		return (free(data->line),
			print_error("Extra textures"), 1);
	if (save_map(data))
		return (1);
	return (0);
}

int	parser(t_data *data, char *file)
{
	char	*texture;

	texture = NULL;
	data->fd = open(file, O_RDONLY);
	if (data->fd == -1)
		return (printf("Error: Invalid file\n"), 1);
	data->line = get_next_line(data->fd);
	if (!data->line)
		return (printf("Error: Empty file\n"), 1);
	if (check_textures(data, &texture) == 1)
		return (free(texture), 1);
	if (load_textures(data, texture, 0, 0) == 1)
		return (1);
	if (!data->no || !data->so || !data->ea || !data->we)
		return (free(data->line), print_error("Missing textures"), 1);
	if (!data->ceiling || !data->floor)
		return (free(data->line), print_error("Missing RGB digits"), 1);
	return (0);
}
