#include "../includes/cub3d.h"

void	draw_slice(t_param *p, int x, int dist)
{
	int	psh;
	t_pt	a;

	psh = p->sizeconst * dist;

	a.y = (p->window->y/2) - (psh/2);

	draw_line((t_pt){x, a.y}, (t_pt){x, p->window->y/2 + psh/2}, 16777215, p);
}

/*
   t_ray	ray_init(int angle, t_param *p)
   {
   }

   int	dda(int angle, t_param *p)
   {
   }
   */

int	oobcheck(t_pt point, t_param *p)
{
	if (point.x < 0 || point.y < 0 || point.x >= p->map->sizeX || point.y >= p->map->sizeY)
		return (1);
	return (0);
}

int	cast_ray(double angle, t_param *p)
{
	t_pt	H;
	t_pt	V;
	t_pt	Ha;
	t_pt	Va;
	int	hit;
	int	disth;
	int	distv;
	int	dist;

	hit = 0;
	dist = 0;
	disth = 0;
	distv = 0;

	printf("\n\ntrying to cast ray with angle %f\n--------------\n", angle);

	H.y = (angle < 180) ? (round(p->camera->y/64) * (64) - 1)/64 : (round(p->camera->y/64) * (64) + 64)/64;
	H.x = (p->camera->x + (p->camera->y - H.y)/tan(angle *0.017))/64;
	ft_printf("first hori intersection coords: %d, %d \n", H.y, H.x);

	if (!oobcheck(H, p))
	{
		ft_printf("first hori intersection value: %d\n", p->map->grid[H.y][H.x]);
		Ha.y = (angle < 180) ? -64 : 64;
		Ha.x = 64/tan(angle*0.017);

		if (p->map->grid[H.y][H.x] == 49)
			disth = fabs((p->camera->x - H.x*64) /cos(angle*0.017));
	}
	V.x = (angle > 90 && angle < 270) ? (p->camera->x/64 * (64) + 64)/64: (p->camera->x/64 * (64) - 1)/64;
	V.y = (p->camera->y + V.x * tan(angle*0.017))/64;
	ft_printf("first vert intersection coords: %d, %d \n", V.y, V.x);

	if (!oobcheck(V, p))
	{
		ft_printf("first vert intersection value: %d\n", p->map->grid[V.y][V.x]);
		Va.x = (angle > 90 || angle < 270) ? 64 : -64;
		Va.y = 64*tan(angle*0.017);

		if (p->map->grid[V.y][V.x] == 49 && disth > abs(p->camera->y - V.y) /sin(angle*0.017))
			distv = fabs((p->camera->y - V.y*64) /sin(angle*0.017));
	}

	int i = 0;
	if (disth || distv)
	{
		dist = (distv) ? distv : disth;
		printf("returning dist: %d\n", dist);
		return (dist);
	}
	else {
		H.x += Ha.x/64;
		H.y += Ha.y/64;
		V.x += Va.x/64;
		V.y += Va.y/64;
		while (!hit)
		{
			if (!oobcheck(H,p))
			{
				printf("next horizontal intersection: %d, %d\n", H.y, H.x);
				ft_printf("next horizontal intersection value: %d\n", p->map->grid[H.y][H.x]);
				if (p->map->grid[H.y][H.x] == 49)
				{
					hit = 1;
					disth = fabs((p->camera->x - H.x*64) /cos(angle*0.017));
					ft_printf("disth = %d\n", disth);
				}
			}
			if (!oobcheck(V, p))
			{
				printf("next vertical intersection: %d, %d\n", V.y, V.x);
				ft_printf("next vertical intersection value: %d\n", p->map->grid[V.y][V.x]);
				if (p->map->grid[V.y][V.x] == 49)
				{
					hit = 1;
					distv = fabs((p->camera->y - V.y*64) /sin(angle*0.017));
					ft_printf("distv = %d\n", distv);
				}
			}
			if (hit)
			{
				dist = (distv < disth && distv != 0) ? distv : disth;
				return (dist);
			}
			else
			{
				if (oobcheck(H,p) && oobcheck(V,p))
				{
					printf("error casting ray\n");
					return (0);
				}
				H.x += Ha.x/64;
				H.y += Ha.y/64;
				V.x += Va.x/64;
				V.y += Va.y/64;
			}
			i++;
			printf("------------\n");
		}

		return (dist);
	}
}
int	cast_rays(t_param *p)
{
	double	angle;
	double	incr;
	int	i;
	int	dist;

	i = 0;
	angle = (double)(p->camera->direction - 30);
	if (angle < 0)
		angle = 360 - angle;
	incr = (double)60/p->window->x;
	while (i < p->window->x)
	{
		dist = cast_ray(angle, p);
		//if (dist)
		draw_slice(p, i, dist);
		angle += incr;
		if (angle > 360)
			angle -= 360;
		i++;
	}
	return (1);
}
