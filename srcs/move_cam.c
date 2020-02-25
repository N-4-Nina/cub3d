#include "../includes/cub3d.h"

void	move_cam(char d, t_param *p)
{
	if (d == 'z')
	{
		p->camera->x = p->camera->x + cos((p->camera->direction) * 0.0174533)*2;
		p->camera->y = p->camera->y + sin((p->camera->direction) * 0.0174533)*2;
	}
	if (d == 's')
	{
		p->camera->x = p->camera->x - cos((p->camera->direction) * 0.0174533)*2;
		p->camera->y = p->camera->y - sin((p->camera->direction) * 0.0174533)*2;
	}
}

void	turn_cam(int i, t_param *p)
{
	p->camera->direction += i;
	if (p-> camera->direction >= 360)
		p->camera->direction = 0;
	else if (p-> camera->direction < 0)
		p->camera->direction = 359;
}
