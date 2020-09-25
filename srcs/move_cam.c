#include "../includes/cub3d.h"

void	move_cam(t_param *p)
{
	if (p->key[FORWARD])
	{
		if (p->map->grid[I(p->pos.x + 2*(p->dir.x * p->speed))][I(p->pos.y)] == 79)
		{
			p->pos.x += p->dir.x * p->speed;
			p->camera->x += p->dir.x * p->speed;
		}
		if (p->map->grid[I(p->pos.x)][I(p->pos.y + 2*(p->dir.y * p->speed))] == 79)
		{
			p->pos.y += p->dir.y * p->speed;
			p->camera->y += p->camera->y * p->speed;
		}
	}
	if (p->key[BACK])
	{
		if (p->map->grid[I(p->pos.x - 2*(p->dir.x * p->speed))][I(p->pos.y)] == 79)
		{
			p->pos.x -= p->dir.x * p->speed;
			p->camera->x -= p->dir.x * p->speed;
		}
		if (p->map->grid[I(p->pos.x)][I(p->pos.y - 2*(p->dir.y * p->speed))] == 79)
		{
			p->pos.y -= p->dir.y * p->speed;
			p->camera->y -= p->camera->y * p->speed;
		}
	}
}

void	turn(t_param *p)
{
	double oldDirX;
	double oldPlaneX;

	if (p->key[LTURN])
	{
	oldDirX = p->dir.x;
	p->dir.x = p->dir.x * cos(-p->rotspeed) - p->dir.y * sin(-p->rotspeed);
	p->dir.y = oldDirX * sin(-p->rotspeed) + p->dir.y * cos(-p->rotspeed);
	oldPlaneX = p->plane.x;
	p->plane.x = p->plane.x * cos(-p->rotspeed) - p->plane.y * sin(-p->rotspeed);
	p->plane.y = oldPlaneX * sin(-p->rotspeed) + p->plane.y * cos(-p->rotspeed);
}
	if (p->key[RTURN])
	{
	double oldDirX = p->dir.x;
  p->dir.x = p->dir.x * cos(p->rotspeed) - p->dir.y * sin(p->rotspeed);
  p->dir.y = oldDirX * sin(p->rotspeed) + p->dir.y * cos(p->rotspeed);
  double oldPlaneX = p->plane.x;
  p->plane.x = p->plane.x * cos(p->rotspeed) - p->plane.y * sin(p->rotspeed);
  p->plane.y = oldPlaneX * sin(p->rotspeed) + p->plane.y * cos(p->rotspeed);
	}
}
