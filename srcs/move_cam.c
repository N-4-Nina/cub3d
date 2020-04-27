#include "../includes/cub3d.h"

void	move_cam(t_param *p)
{
	if (p->key[126])
	{
		if (p->map->grid[I(p->pos.x + p->dir.x * p->speed)][I(p->pos.y)] == 48)
		{
			p->pos.x += p->dir.x * p->speed;
			p->camera->x += p->dir.x * p->speed;
		}
		if (p->map->grid[I(p->pos.x)][I(p->pos.y + p->dir.y * p->speed)] == 48)
		{
			p->pos.y += p->dir.y * p->speed;
			p->camera->y += p->camera->y * p->speed;
		}
	}
	if (p->key[125])
	{
		if (p->map->grid[I(p->pos.x - p->dir.x * p->speed)][I(p->pos.y)] == 48)
		{
			p->pos.x -= p->dir.x * p->speed;
			p->camera->x -= p->dir.x * p->speed;
		}
		if (p->map->grid[I(p->pos.x)][I(p->pos.y - p->dir.y * p->speed)] == 48)
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

	if (p->key[124])
	{
	oldDirX = p->dir.x;
	p->dir.x = p->dir.x * cos(-p->rotspeed) - p->dir.y * sin(-p->rotspeed);
	p->dir.y = oldDirX * sin(-p->rotspeed) + p->dir.y * cos(-p->rotspeed);
	oldPlaneX = p->plane.x;
	p->plane.x = p->plane.x * cos(-p->rotspeed) - p->plane.y * sin(-p->rotspeed);
	p->plane.y = oldPlaneX * sin(-p->rotspeed) + p->plane.y * cos(-p->rotspeed);
}
	if (p->key[123])
	{
	double oldDirX = p->dir.x;
  p->dir.x = p->dir.x * cos(p->rotspeed) - p->dir.y * sin(p->rotspeed);
  p->dir.y = oldDirX * sin(p->rotspeed) + p->dir.y * cos(p->rotspeed);
  double oldPlaneX = p->plane.x;
  p->plane.x = p->plane.x * cos(p->rotspeed) - p->plane.y * sin(p->rotspeed);
  p->plane.y = oldPlaneX * sin(p->rotspeed) + p->plane.y * cos(p->rotspeed);
}
}
