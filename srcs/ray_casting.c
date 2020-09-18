#include "../includes/cub3d.h"

int	check_hit(t_param *p)
{
	if (p->mappt.x < 0. || p->mappt.y < 0. || p->mappt.x >= FT(p->map->size.x) || p->mappt.y >= FT(p->map->size.y))
		return (0);
	if (p->map->grid[p->mappt.x][p->mappt.y] == 50)
	{
			p->isSprite = 1;
			//p->spriteDist.x =
	}
	if (p->map->grid[p->mappt.x][p->mappt.y] == 49)
		p->hit = 1;
	return (1);
}

void	dda(t_param *p)
{
	p->hit = 0;
	p->isSprite = 0;
	while (p-> hit == 0)
	{
		if (p->sidedist.x < p->sidedist.y)
		{
			p->sidedist.x += p->delta.x;
			p->mappt.x += p->step.x;
			p->side = 0;
		}
		else
		{
			p->sidedist.y += p->delta.y;
			p->mappt.y += p->step.y;
			p->side = 1;
		}
		if (!(check_hit(p)))
			break;
	}
}


void	dda_init(t_param *p)
{
	p->delta.x = sqrt(1 + (p->raydir.y * p->raydir.y)
			/ (p->raydir.x * p->raydir.x));
	p->delta.y = sqrt(1 + (p->raydir.x * p->raydir.x)
			/ (p->raydir.y * p->raydir.y));
	if (p->raydir.x < 0)
	{
		p->step.x = -1;
		p->sidedist.x = (p->raypos.x - p->mappt.x) * p->delta.x;
	}
	else
	{
		p->step.x = 1;
		p->sidedist.x = (p->mappt.x + 1.0 - p->raypos.x) * p->delta.x;
	}
	if (p->raydir.y < 0)
	{
		p->step.y = -1;
		p->sidedist.y = (p->raypos.y - p->mappt.y) * p->delta.y;
	}
	else
	{
		p->step.y = 1;
		p->sidedist.y = (p->mappt.y + 1.0 - p->raypos.y) * p->delta.y;
	}
}

void	ray_init(t_param *p, int x)
{
	p->x_cam = 2 * x / (double)(p->window->x) - 1;
	p->raypos.x = p->pos.x;
	p->raypos.y = p->pos.y;
	p->raydir.x = p->dir.x + p->plane.x * p->x_cam;
	p->raydir.y = p->dir.y + p->plane.y * p->x_cam;
	p->mappt.x = I(p->raypos.x);
	p->mappt.y = I(p->raypos.y);
	dda_init(p);
	dda(p);
	if (p->side == 0)
		p->walldist = (p->mappt.x - p->raypos.x +
				(1 - p->step.x) / 2) / p->raydir.x;
	else
		p->walldist = (p->mappt.y - p->raypos.y +
				(1 - p->step.y) / 2) / p->raydir.y;
}
void wall_height(t_param *p)
{
	p->height = I(p->window->y / p->walldist);
	p->top = -p->height / 2 + p->window->y /2;
	p->top = (p->top < 0) ? 0 : p->top;
	p->bot = p->height / 2 + p->window->y /2;
	p->bot = (p->bot < 0) ? 0 : p->bot;
}
void sprite_height(t_param *p)
{
	p->sHeight =
}
void	ray_casting(t_param *p)
{
	p->x = -1;
	p->frame = mlx_new_image(p->window->mlx, p->window->x, p->window->y);
	p->frameptr = mlx_get_data_addr(p->frame, &p->bpp, &p->sl, &p->endian);
	while (++p->x < p->window->x)
	{
		ray_init(p, p->x);
		wall_height(p);
		if (p->isSprite)
			sprite_height(t_param *p)
		add_slice(p->x, p->top-1, p->bot, p);
	}
	mlx_put_image_to_window(p->window->mlx, p->window->window, p->frame, 0, 0);
	mlx_do_sync(p->window->mlx);
	//mlx_destroy_image(p->window->mlx, p->frame);
}
