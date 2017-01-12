/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:37:51 by lsimon            #+#    #+#             */
/*   Updated: 2017/01/12 12:04:57 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_color		new_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color new;

	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}
