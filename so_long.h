/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:53:16 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/09 21:20:52 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# define BUFFER_SIZE 42

typedef struct s_map
{
	int		rows;
	int		has_c;
	int		has_e;
	int		has_p;
	int		diff_cols;
	char	**lines;
	size_t	cols;
}	t_map;

/* get_next_line.c */
char	*get_next_line(int fd);

#endif
