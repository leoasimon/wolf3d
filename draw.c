/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becorbel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:09:01 by becorbel          #+#    #+#             */
/*   Updated: 2017/01/12 11:52:24 by becorbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	init(t_data *d, int x)
{
	d->camerax = 2 * x / (double)WIDTH - 1;
	d->rayposx = d->posx;
	d->rayposy = d->posy;
	d->raydirx = d->dirx + d->planex * d->camerax;
	d->raydiry = d->diry + d->planey * d->camerax;
	d->mapx = (int)d->rayposx;
	d->mapy = (int)d->rayposy;
	d->deltadistx = sqrt(1 + (d->raydiry * d->raydiry) /
			(d->raydirx * d->raydirx));
	d->deltadisty = sqrt(1 + (d->raydirx * d->raydirx) /
			(d->raydiry * d->raydiry));
	d->hit = 0;
}

void	step_calc(t_data *d)
{
	if (d->raydirx < 0)
	{
		d->stepx = -1;
		d->sidedistx = (d->rayposx - d->mapx) * d->deltadistx;
	}
	else
	{
		d->stepx = 1;
		d->sidedistx = (d->mapx + 1.0 - d->rayposx) * d->deltadistx;
	}
	if (d->raydiry < 0)
	{
		d->stepy = -1;
		d->sidedisty = (d->rayposy - d->mapy) * d->deltadisty;
	}
	else
	{
		d->stepy = 1;
		d->sidedisty = (d->mapy + 1.0 - d->rayposy) * d->deltadisty;
	}
}

void	hit_square(t_data *d, int worldmap[24][24])
{
	while (d->hit == 0)
	{
		if (d->sidedistx < d->sidedisty)
		{
			d->sidedistx += d->deltadistx;
			d->mapx += d->stepx;
			d->side = 0;
		}
		else
		{
			d->sidedisty += d->deltadisty;
			d->mapy += d->stepy;
			d->side = 1;
		}
		if (worldmap[d->mapx][d->mapy] > 0)
			d->hit = 1;
	}
}

void	dist_calc(t_data *d)
{
	if (d->side == 0)
		d->perpwalldist = (d->mapx - d->rayposx + (1 - d->stepx) /
				2) / d->raydirx;
	else
		d->perpwalldist = (d->mapy - d->rayposy + (1 - d->stepy) /
				2) / d->raydiry;
	d->lineheight = (int)(HEIGHT / d->perpwalldist);
	d->drawstart = -d->lineheight / 2 + HEIGHT / 2;
	if (d->drawstart < 0)
		d->drawstart = 0;
	d->drawend = d->lineheight / 2 + HEIGHT / 2;
	if (d->drawend >= HEIGHT)
		d->drawend = HEIGHT - 1;
}

int		draw(t_data *d)
{
	t_color	color;
	int		x;
	int		worldmap[24][24]=
	{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	color = new_color(168, 128, 72);
	x = -1;
	while (x++ < WIDTH)
	{
		init(d, x);
		step_calc(d);
		hit_square(d, worldmap);
		dist_calc(d);
		line(x, color, *d);
	}
	mlx_put_image_to_window(d->mlx, d->w, d->img, 0, 0);
	return (0);
}
