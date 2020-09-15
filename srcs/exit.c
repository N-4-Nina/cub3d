#include "../includes/cub3d.h"

void free_and_exit(t_param *p)
{
  free(p->map );
	free(p->window);
	free(p->color);
	free(p->camera);
  exit(1);
}
