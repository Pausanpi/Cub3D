/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:48:18 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/27 16:08:06 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

static void	ifs(t_data *d, char **texture)
{
	if (d->line[0] == '\n')
		d->line[0] = '\n';
	else if ((ft_strncmp(d->line, "NO", 2)
			|| ft_strncmp(d->line, "SO", 2) || ft_strncmp(d->line, "WE", 2)
			|| ft_strncmp(d->line, "EA", 2)) && (d->line[2] == ' '
			|| (d->line[2] >= 9 && d->line[3] <= 13)))
		gnl_texture(d, texture);
	else if ((ft_strncmp(d->line, "F", 1)
			|| ft_strncmp(d->line, "C", 1)) && (d->line[1] == ' '
			|| (d->line[1] >= 9 && d->line[2] <= 13)))
		gnl_texture(d, texture);
	else if (d->line)
		d->texture_count++;
}

int	check_textures(t_data *d, char **texture)
{
	while (d->line && d->line[0] != '1' && d->line[0] != ' ')
	{
		ifs(d, texture);
		free(d->line);
		d->line = get_next_line(d->fd);
		if (d->line && d->line[0] >= 9 && d->line[0] <= 13)
		{
			free(d->line);
			d->line = get_next_line(d->fd);
		}
	}
	if (d->texture_count != 6)
		return (free(d->line), print_error("Incorrect number textures"), 1);
	if (save_map(d))
		return (1);
	return (0);
}

int	parser(t_data *d, char *file)
{
	char	*texture;

	texture = NULL;
	d->fd = open(file, O_RDONLY);
	if (d->fd == -1)
		return (printf("Error: Invalid file\n"), 1);
	d->line = get_next_line(d->fd);
	if (!d->line)
		return (printf("Error: Empty file\n"), 1);
	if (check_textures(d, &texture) == 1)
		return (free(texture), 1);
	if (load_textures(d, texture, 0) == 1)
		return (1);
	if (!d->no || !d->so || !d->ea || !d->we)
		return (free(d->line), print_error("Missing textures"), 1);
	if (!d->ceiling || !d->floor)
		return (free(d->line), print_error("Missing RGB digits"), 1);
	return (0);
}
