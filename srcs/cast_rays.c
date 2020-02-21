#include "../includes/cub3d.h"

void	draw_slice(t_param *p, int x, int dist)
{
	int	psh;
	t_pt	a;

	psh = (277*64) /dist;

	a.y = (p->window->y/2) - (psh/2);

	draw_line((t_pt){x, a.y}, (t_pt){x, p->window->y/2 + psh/2}, 16777215, p);
}
/*
   int	hori_check(int angle, t_param *p)
   {
   int	dist;


   }


   int	vert_check(int angle, t_param *p)
   {
   t_pt	R;


   }

   int	cast_ray(int angle, t_param *p)
   {
   t_pt	H;
   t_pt	Rh;
   t_pt	V;
   t_pt	Rv;
   int	hdist;
   int	vdist;
   int	dist;

   printf("casting ray with angle %d\n--------------\n\n", angle);

   H.y = (angle < 180) ? round(p->camera->y/64) * (64) - 1 : round(p->camera->y/64) * (64) + 64;
   H.x = p->camera->x + (p->camera->y - H.y)/tan(angle);
   H.x /= 64;
   H.y /= 64;
   Rh.x = 64/tan(angle);
   Rh.y = (angle > 180) ? -64 : 64;

   V.x = (angle > 90 && angle < 270) ? round(p->camera->x/64) *64 + 64 : round(p->camera->x/64) *64 - 1;
   V.y = p->camera->y - (p->camera->x - V.x)*tan(p->camera->direction);
   V.x /= 64;
   V.y /= 64;
   V.y = (V.y < 0 || V.y > p->map->sizeY) ? 0 : V.y;
   Rv.x = (angle > 90 && angle < 270) ? 64 : -64;
   Rv.y = 64*tan(angle);

   ft_printf("first hori intersection coords: %d, %d \n", H.y, H.x);
   ft_printf("first hori intersection value: %d\n", p->map->grid[H.y][H.x]);
   ft_printf("first vert intersection coords: %d, %d \n", V.y, V.x);
   ft_printf("first vert intersection value: %d\n", p->map->grid[V.y][V.x]);

   int	i = 0;
   while (V.y < 14 && H.x < 30 && p->map->grid[H.y][H.x] != 49 && p->map->grid[V.y][V.x] != 49 && i < 10)
   {
   if (H.x != p->map->sizeX-1 && H.y != p->map->sizeY-1)
   {
   H.x += Rh.x/64;
   H.y += Rh.y/64;
   H.x--;
   printf("next horizontal intersection: %d, %d\n", H.y, H.x);
   ft_printf("next hori intersection value: %d\n", p->map->grid[H.y][H.x]);
   }
   if (V.x != p->map->sizeX-1 && V.y != p->map->sizeY-1)
   {
   V.x += Rv.x/64;
   V.y += Rv.y/64;
   V.y--;
   printf("next vertical intersection: %d, %d\n", V.y, V.x);
   ft_printf("next vertical intersection value: %d\n", p->map->grid[V.y][V.x]);
   }
   i++;
   printf("------------\n");
   }

if (p->map->grid[H.y][H.x] == 49 && p->map->grid[V.y][V.x] == 49)
{
	hdist = abs(p->camera->x - H.x) /cos(angle);
	vdist = abs(p->camera->y - V.y) /sin(angle);
	dist = (hdist > vdist) ? vdist : hdist;
}

if (p->map->grid[H.y][H.x] == 49)
	dist = abs(p->camera->x - H.x) /cos(angle);
else if (p->map->grid[V.y][V.x] == 49)
	dist = abs(p->camera->y - V.y) /sin(angle);
	else
{
	printf("big oops\n");
	return (0);
}
dist *= cos((p->camera->direction - angle));
ft_printf("\nreturning distance %d for ray with angle %d\n---------------\n\n", dist, angle);
return (dist);
}
*/

int	cast_ray(int angle, t_param *p)
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

   	printf("\n\ntrying to cast ray with angle %d\n--------------\n", angle);

	H.y = (angle < 180) ? (round(p->camera->y/64) * (64) - 1)/64 : (round(p->camera->y/64) * (64) + 64)/64;
	H.x = (p->camera->x + (p->camera->y - H.y)/tan(angle*0.017))/64;
	ft_printf("first hori intersection coords: %d, %d \n", H.y, H.x);
	ft_printf("first hori intersection value: %d\n", p->map->grid[H.y][H.x]);

	Ha.y = (angle<180) ? -64 : 64;
	Ha.x = 64/tan(angle);

	if (p->map->grid[H.y][H.x] == 49)
		disth = abs(p->camera->x - H.x) /cos(angle);

	V.x = (angle > 90 && angle < 270) ? (p->camera->x/64 * (64) + 64)/64: (p->camera->x/64 * (64) - 1)/64;
	V.y = (p->camera->y + V.x * tan(p->camera->direction))/64;

	Va.x = (angle > 90 || angle < 270) ? 64 : -64;
	Va.y = 64*tan(angle);

	if (p->map->grid[V.y][V.x] == 49 && disth > abs(p->camera->y - V.y) /sin (angle))
		distv = (abs(p->camera->y - V.y) /sin(angle));

	int i = 0;
	ft_printf("first vert intersection coords: %d, %d \n", V.y, V.x);
	ft_printf("first vert intersection value: %d\n", p->map->grid[V.y][V.x]);
	if (disth || distv)
	{
		dist = (distv) ? distv : disth;
		return (dist);
	}
	else {
		while (!hit && i > 10)
		{
			if (H.x > 0 && H.x < p->map->sizeX-1 && H.y > 0 && H.y < p->map->sizeY-1)
			{
				H.x += Ha.x/64;
				H.y += Ha.y/64;
				//H.x--;
				printf("next horizontal intersection: %d, %d\n", H.y, H.x);
				ft_printf("next horizontal intersection value: %d\n", p->map->grid[H.y][H.x]);
			}
			if (V.x > 0 && V.x < p->map->sizeX-1 && V.y > 0 && V.y < p->map->sizeY-1)
			{
				V.x += Va.x/64;
				V.y += Va.y/64;
				//V.y--;
				printf("next vertical intersection: %d, %d\n", V.y, V.x);
				ft_printf("next vertical intersection value: %d\n", p->map->grid[V.y][V.x]);
			}
			if (p->map->grid[H.y][H.x] == 49)
			{
				hit = 1;
				disth = abs(p->camera->x - H.x) /cos(angle);
			}
			if (p->map->grid[V.y][V.x] == 49 && disth > abs(p->camera->y - V.y) /sin (angle))
			{
				hit = 1;
				distv = (abs(p->camera->y - V.y) /sin(angle));
			}
			if (hit)
			{
				dist = (distv) ? distv : disth;
				return (64/dist*277);
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
			dist = cast_ray((int)angle, p);
			if (dist)
				draw_slice(p, i, dist);
			angle += incr;
			if (angle > 360)
				angle -= 360;
			i++;
		}
		return (1);
	}
