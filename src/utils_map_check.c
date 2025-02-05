/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:59:08 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/05 14:27:23 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	gnl_texture(t_data *data, char **texture)
{
	*texture = gnl_ft_strjoin2(*texture, data->line);
	data->texture_count++;
}

char	*gnl_ft_strjoin2(char *s1, char *s2)
{
	int		i;
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*s3;

	if (s1 == NULL)
	{
		s1 = ft_calloc(1, sizeof(char));
		if (!s1)
			return (free(s1), s1 = NULL, NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = len1 + len2;
	i = len1;
	s3 = malloc((len3 + 1) * sizeof(char));
	if (s3 == 0)
		return (free(s1), s1 = NULL, NULL);
	ft_memcpy(s3, s1, len1);
	ft_memcpy(&s3[i], s2, (len2 + 1));
	return (free(s1), s1 = NULL, s3);
}

int	check_first_line(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map && data->map[i])
	{
		while (i == 0 && (data->map[i][j] == 32
			|| (data->map[i][j] >= 9 && data->map[i][j] <= 13)))
			j++;
		if (i == 0 && (data->map[i][j] != '1'
			|| data->map[i][ft_strlen(data->map[i]) - 1] != '1'))
			return (print_error("Space in first line"), 1);
		i++;
	}
	return (0);
}

int	ft_bucle(t_data *data, int i, int j)
{
	if (data->map[i][j] != '1' && data->map[i][j] != '0'
		&& data->map[i][j] != 'N' && data->map[i][j] != 'S'
		&& data->map[i][j] != 'E' && data->map[i][j] != 'W'
		&& data->map[i][j] != 32)
		return (print_error("Invalid character"), 1);
	if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
		|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
	{
		data->char_pos++;
		data->orientation = data->map[i][j];
	}
	return (0);
}

size_t	ft_electric_bucleloo(t_data *data)
{
	int i;
	size_t max_l;

	i = -1;
	max_l = 0;
	while (data->map[++i])
	{
		if (max_l < ft_strlen(data->map[i]))
			max_l = ft_strlen(data->map[i]);
	}
	return (max_l);
}
