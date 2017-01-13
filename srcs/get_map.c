/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:21:17 by lsimon            #+#    #+#             */
/*   Updated: 2017/01/13 13:31:44 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

char	*get_map(char *s, t_data d)
{
	int		fd;
	char	*line;
	int		rreturn;

	if ((fd = open(s, O_RDONLY)) < 0)
		return (NULL);
	if ((rreturn = ft_get_next_line(fd, &line)) < 0)
		return (NULL);
	d->mapw = ft_strlen(line);
	
}