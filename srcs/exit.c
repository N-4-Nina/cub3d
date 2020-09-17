#include "../includes/cub3d.h"


void free_grid(t_param *p)
{
    int i;

    i = 0;
    while (i < p->map->size.x)
    {
      free(p->map->grid[i]);
      i++;
    }
}

int free_and_exit(t_param *p)
{
  free_grid(p);
  free(p->frame);
  free(p->map);
  free(p->window -> mlx);
	free(p->window);
	free(p->color);
	free(p->camera);
  exit(1);
}
