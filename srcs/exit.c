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
  int i;

  i = 0;
  free_grid(p);
  mlx_destroy_image(p->window->mlx, p->frame);
  while (i < 5)
  {
    free(p->tex[i].img);
    i++;
  }
  free(p->map);
  free(p->window -> mlx);
	free(p->window);
	free(p->color);
	free(p->camera);
  exit(1);
}
