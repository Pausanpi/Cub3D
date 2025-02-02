/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:48:18 by pausanch          #+#    #+#             */
/*   Updated: 2025/01/31 18:43:09 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

int parser(t_data *data, char *file)
{
    char *texture;

    texture = NULL;
    data->fd = open(file, O_RDONLY);
    if (data->fd == -1)
        return (printf("Error: Invalid file\n"), 1);
    data->line = get_next_line(data->fd);
    if (!data->line)
        return (printf("Error: Empty file\n"), 1);
    if (check_textures(data, &texture) == 1)
	{
        return (1);
	}
	load_textures(data, texture); // habria que hacer un check de esto
	if (!data->no || !data->so || !data->ea || !data->we)
		return(free(data->line), printf("Error: Missing textures\n"), 1);
	if (!data->ceiling || !data->floor)
		return(free(data->line), printf("Error: Missing RGB colors\n"), 1);
    return (0);
}