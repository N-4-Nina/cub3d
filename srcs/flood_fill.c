#include "../includes/cub3d.h"

int reached_limit(t_param *p, t_pt pt)
{
  return(pt.x == 0 || pt.y == 0 || pt.x == p->map->size.x - 1 || pt.y == p->map->size.y - 1);
}

int can_access(char **grid, t_pt pt)
{
  return(!!(ft_strchr("0,2", grid[pt.x][pt.y])));
}

void flood_fill(t_param *p, t_pt coord)
{
  p->map->grid[coord.x][coord.y] = 'O';
  if (reached_limit(p, coord))
  {
    write(1, "map should be closed by walls.", 30);
    free_and_exit(p);
  }

  if(can_access(p->map->grid, (t_pt){coord.x-1, coord.y}))
    flood_fill(p, (t_pt){coord.x-1, coord.y});
  if(can_access(p->map->grid, (t_pt){coord.x+1, coord.y}))
    flood_fill(p, (t_pt){coord.x+1, coord.y});
  if(can_access(p->map->grid, (t_pt){coord.x, coord.y-1}))
    flood_fill(p, (t_pt){coord.x, coord.y-1});
  if(can_access(p->map->grid, (t_pt){coord.x, coord.y+1}))
    flood_fill(p, (t_pt){coord.x, coord.y+1});
}
