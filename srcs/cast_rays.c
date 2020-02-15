#include "../includes/cub3d.h"

int	cast_ray(int angle, t_param *p)
{
	int	i;
	int	lx;
	int	ly;

	i = 1;
	lx = p->camera->x - cos((angle) * 0.0174533)*i;
	ly = p->camera->y - sin((angle) * 0.0174533)*i;
	while (lx % 64 != 0 && ly % 64 != 0)
	{
		lx = p->camera->x - cos((angle) * 0.0174533)*i;
		ly = p->camera->y - sin((angle) * 0.0174533)*i;
		i++;
	}
	draw_line((t_pt){p->camera->x, p->camera->y}, (t_pt){lx, ly}, 16777215, p);
	return (1);
}

int	cast_rays(t_param *p)
{
	int	angle;

	angle = p->camera->direction - 30;
	draw_line((t_pt){p->camera->x, p->camera->y}, (t_pt){p->camera->x, p->camera->y-45}, 0xFEFEFE, p);
	while (angle < p->camera->direction+30)
	{
		//ft_printf("%d\n", angle);
		cast_ray(angle, p);
		angle += 1;
	}
	return (1);
}
