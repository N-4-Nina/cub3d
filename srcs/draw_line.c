#include "../includes/cub3d.h"

void	linedraw_init(t_pt pt, t_pt pt1, int color, t_linedraw *s)
{
	s->delta.x = pt1.x - pt.x;
	s->delta.y = pt1.y - pt.y;
	s->delta1.x = abs(s->delta.x);
	s->delta1.y = abs(s->delta.y);
	s->p.x = 2 * s->delta1.y - s->delta1.x;
	s->p.y = 2 * s->delta1.x - s->delta1.y;
	s->color = color;
}

void	dl_Xdir(t_pt pt, t_pt pt1, t_linedraw *s)
{
	if (s->delta.x >= 0)
	{
		s->ori.x = pt.x;
		s->ori.y = pt.y;
		s->e.x = pt1.x;
	}
	else
	{
		s->ori.x = pt1.x;
		s->ori.y = pt1.y;
		s->e.x = pt.x;
	}
}

void	dl_Ydir(t_pt pt, t_pt pt1, t_linedraw *s)
{
	if (s->delta.y >= 0)
	{
		s->ori.x = pt.x;
		s->ori.y = pt.y;
		s->e.y = pt1.y;
	}
	else
	{
		s->ori.x = pt1.x;
		s->ori.y = pt1.y;
		s->e.y = pt.y;
	}
}

void	dl_Xaxis(t_pt pt, t_pt pt1, t_linedraw *s, t_param *p)
{
	dl_Xdir(pt, pt1, s);
	mlx_pixel_put(p->window->mlx, p->window->window, s->ori.x, s->ori.y, s->color);
	while (s->ori.x < s->e.x)
	{
		s->ori.x++;
		if (s->p.x <= 0)
			s->p.x = s->p.x + 2 * s->delta1.y;
		else
		{
			if ((s->delta.x < 0 && s->delta.y < 0) || (s->delta.x > 0 && s->delta.y > 0))
				s->ori.y++;
			else
				s->ori.y--;
			s->p.x = s->p.x + 2 * (s->delta1.y - s->delta1.x);
		}
		mlx_pixel_put(p->window->mlx, p->window->window, s->ori.x, s->ori.y, s->color);
		s->color--;
	}
	return;
}

void	dl_Yaxis(t_pt pt, t_pt pt1, t_linedraw *s, t_param *p)
{
	dl_Ydir(pt, pt1, s);
	mlx_pixel_put(p->window->mlx, p->window->window, s->ori.x, s->ori.y, s->color);
	while (s->ori.y < s->e.y)
	{
		s->ori.y++;
		if (s->p.y <= 0)
			s->p.y = s->p.y + 2 * s->delta1.x;
		else
		{
			if ((s->delta.x < 0 && s->delta.y < 0) || (s->delta.x > 0 && s->delta.y > 0))
				s->ori.x++;
			else
				s->ori.x--;
			s->p.y = s->p.y + 2 * (s->delta1.x - s->delta1.y);
		}
		mlx_pixel_put(p->window->mlx, p->window->window, s->ori.x, s->ori.y, s->color);
		s->color--;
	}
}

void	draw_line(t_pt pt, t_pt pt1, int color, t_param *p)
{
	t_linedraw	s;

	linedraw_init(pt, pt1, color, &s);

	if (s.delta1.y < s.delta1.x)
		dl_Xaxis(pt, pt1, &s, p);
	else
		dl_Yaxis(pt, pt1, &s, p);
}
