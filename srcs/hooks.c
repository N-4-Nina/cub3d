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
	p->key[keycode] = 0;
	printf("%d\n", keycode);

	return (keycode);
}

int	keypress(int keycode, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	p->key[keycode] = 1;
	if (keycode == 53)
		free_and_exit(p);
	return (keycode);
}
