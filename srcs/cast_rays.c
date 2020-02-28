#include "../includes/cub3d.h"

void	draw_slice(t_param *p, int x, int dist)
{
	int	psh;
	int	ya;
	int	yb;

	psh =  p->scrdist/dist;
	ya = (p->window->y/2) - (psh/2);
	yb = (p->window->y/2) + (psh/2);

	//draw_line((t_pt){x, 0}, (t_pt){x, ya}, p->color->ceiling, p);
	draw_line((t_pt){x, ya}, (t_pt){x, yb}, 16777215, p);
	//draw_line((t_pt){x, yb}, (t_pt){x, p->window->y}, p->color->floor, p);
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
	point.x /= 64;
	point.y /= 64;
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
	printf("camera is at y= %d, x= %d\n", p->camera->y, p->camera->x);

	H.y = (angle < 180) ? round(p->camera->y/64) * 64 - 1 : round(p->camera->y/64) * 64 + 64;
	H.x = p->camera->x + (p->camera->y - H.y)/tan(angle *0.0174533);
	ft_printf("first hori intersection coords: %d, %d \n", H.y/64, H.x/64);

	if (!oobcheck(H, p))
	{
		ft_printf("first hori intersection value: %d\n", p->map->grid[H.y/64][H.x/64]);
		Ha.y = (angle < 180) ? -64 : 64;
		Ha.x = tan(angle*0.017);

		if (p->map->grid[H.y/64][H.x/64] == 49)
			disth = sqrt(pow(p->camera->x - H.x,2)+ pow(p->camera->y-H.y, 2));
	}
	V.x = (angle > 90 && angle < 270) ? round(p->camera->x/64) * 64 + 64 : round(p->camera->x/64) * 64 - 1;
	V.y = (p->camera->y + (p->camera->x - V.x) * tan(angle*0.0174533));
	ft_printf("first vert intersection coords: %d, %d \n", V.y/64, V.x/64);

	if (!oobcheck(V, p))
	{
		ft_printf("first vert intersection value: %d\n", p->map->grid[V.y/64][V.x/64]);
		Va.x = (angle > 90 || angle < 270) ? 64 : -64;
		Va.y = tan(angle*0.017);

		if (p->map->grid[V.y/64][V.x/64] == 49 && disth > abs(p->camera->y - V.y) /sin(angle*0.0174533))
			distv = sqrt(pow(p->camera->x - V.x,2)+ pow(p->camera->y-V.y, 2));
	}

	int i = 0;
	if (disth || distv)
	{
		dist = (distv) ? distv : disth;
		dist = dist * cos((angle - p->camera->direction)*0.0174533);
		printf("returning dist: %d\n", dist);
		return (dist);
	}
	else {
		H.x = round(H.x + Ha.x);
		H.y = round(H.y + Ha.y);
		V.x = round(V.x + Va.x);
		V.y = round(V.y + Va.y);
		while (!hit)
		{
			if (!oobcheck(H,p))
			{
				printf("next horizontal intersection: %d, %d\n", H.y/64, H.x/64);
				ft_printf("next horizontal intersection value: %d\n", p->map->grid[H.y/64][H.x/64]);
				if (p->map->grid[H.y/64][H.x/64] == 49)
				{
					hit = 1;
					disth = sqrt(pow(p->camera->x - H.x,2)+ pow(p->camera->y-H.y, 2));
					ft_printf("disth = %d\n", disth);
				}
			}
			if (!oobcheck(V, p))
			{
				printf("next vertical intersection: %d, %d\n", V.y/64, V.x/64);
				ft_printf("next vertical intersection value: %d\n", p->map->grid[V.y/64][V.x/64]);
				if (p->map->grid[V.y/64][V.x/64] == 49)
				{
					hit = 1;
					distv = sqrt(pow(p->camera->x - V.x,2)+ pow(p->camera->y-V.y, 2));
					ft_printf("distv = %d\n", distv);
				}
			}
			if (hit)
			{
				dist = (distv < disth && distv != 0) ? distv : disth;
				dist = dist * cos((angle - p->camera->direction)*0.0174533);
				return (dist);
			}
			else
			{
				if (oobcheck(H,p) && oobcheck(V,p))
				{
					printf("error casting ray\n");
					return (0);
				}
				H.x = round(H.x + Ha.x);
				H.y = round(H.y + Ha.y);
				V.x = round(V.x + Va.x);
				V.y = round(V.y + Va.y);
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
		if (dist)
			draw_slice(p, p->window->x - i - 1, dist);
		angle += incr;
		if (angle > 360)
			angle -= 360;
		i++;
	}
	return (1);
}
