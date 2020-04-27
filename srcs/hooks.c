#include "../includes/cub3d.h"
int	loop_hook(void *param)
{
	t_param	*p;
	p = (t_param*)param;

  ray_casting(p);
	move_cam(p);
	turn(p);
	//mlx_clear_window(p->window->mlx, p->window->window);
	return (1);
}

int	keyrelease(int keycode, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	if (keycode == 41)
		p->key[41] = 0;
	if (keycode == 123)
			p->key[123] = 0;
	if (keycode == 124)
			p->key[124] = 0;
	if (keycode == 126)
		p->key[126] = 0;
	if (keycode == 125)
		p->key[125] = 0;
	return (keycode);
}

int	keypress(int keycode, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	if (keycode == 53)
		exit(keycode);
	if (keycode == 41)
		p->key[41] = 1;
	if (keycode == 123)
			p->key[123] = 1;
	if (keycode == 124)
			p->key[124] = 1;
	if (keycode == 126)
		p->key[126] = 1;
	if (keycode == 125)
		p->key[125] = 1;
	if (keycode == 35)
		check_print(p);
	else
		ft_printf("keycode = %d. \n", keycode);
	return (keycode);
}
