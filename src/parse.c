/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:48:18 by pausanch          #+#    #+#             */
/*   Updated: 2025/01/28 12:48:24 by pausanch         ###   ########.fr       */
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
        return (1);
    return (0);
}