/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:09:53 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/11 17:55:15 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "so_long.h"
#include "libft/libft.h"

static int	char_count(char *line, int c)
{
	int	ret;

	ret = 0;
	while (*line)
		if (*line++ == c)
			++ret;
	return (ret);
}

static int	is_set(char *line, char *set)
{
	int			i;
	char		*tmp;
	const int	len = ft_strlen(line);

	i = 0;
	while (*line)
	{
		tmp = set;
		while (*tmp)
			if (*line == *tmp++)
				++i;
		++line;
	}
	if (i != len)
		return (0);
	return (1);
}

static int	is_ber(char *file)
{
	const char	*ext = ft_strrchr(file, '.');
	const int	len = ft_strlen(ext);

	if (!ft_strncmp(ext, ".ber", len))
		return (1);
	return (0);
}

static int	is_rectangular_and_cep(char *file, t_map *map)
{
	int			i;
	char		*line;
	const int	fd = open(file, O_RDONLY);

	i = 0;
	line = get_next_line(fd);
	while (line && ++i)
	{
		if (i == 1)
			map->cols = ft_strlen(line);
		else if ((int)ft_strlen(line) != map->cols)
			map->diff_cols = 1;
		if (ft_strchr(line, 'C'))
			map->c += char_count(line, 'C');
		if (ft_strchr(line, 'E'))
			map->e += char_count(line, 'E');
		if (ft_strchr(line, 'P'))
			map->p += char_count(line, 'P');
		free(line);
		line = get_next_line(fd);
	}
	map->rows = i;
	if (!map->c || !map->e || map->p != 1 || map->diff_cols)
		return (0);
	return (1);
}

int	is_valid_map(char *file, t_map *map)
{
	int			i;
	int			is_valid;
	char		*line;
	const int	fd = open(file, O_RDONLY);

	is_valid = 1;
	if (!is_ber(file) || !is_rectangular_and_cep(file, map))
		is_valid = 0;
	i = 0;
	line = get_next_line(fd);
	while (line && ++i)
	{
		if ((i == 1 || i == map->rows) && !is_set(line, "1"))
			is_valid = 0;
		else if (i != 1 && i != map->rows && (!is_set(line, "01CEP") \
				|| line[0] != '1' || line[map->cols - 1] != '1'))
			is_valid = 0;
		free(line);
		line = get_next_line(fd);
	}
	if (!is_valid)
		return (0);
	return (1);
}
