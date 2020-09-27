#include "../includes/cub3d.h"

double sprite_dist(t_param *p, int side)
{
  if (side == 0)
    return(p->mappt.x - p->raypos.x +
        (1 - p->step.x) / 2) / p->raydir.x;
  else
    return(p->mappt.y - p->raypos.y +
        (1 - p->step.y) / 2) / p->raydir.y;
}

void add_sprite(t_param *p, t_pt coord, int side)
{
  int i;

  i = 0;
  while (i < p->spritesnb)
    i++;
  p->sprites[i] = (t_sprites*)malloc(sizeof(t_sprites));
  p->sprites[i]->coord = coord;
  p->sprites[i]->side = side;
  p->sprites[i]->dist = sprite_dist(p, side);
  p->sprites[i]->raypos = p->raypos;
  p->spritesnb++;

}

void free_sprites(t_param *p)
{
  int i;

  i = 0;

  while (i < p->spritesnb)
    free(p->sprites[i++]);
  p->spritesnb = 0;
}

void  sprite_to_frame(int x, int y, t_param *p)
{
	if (x < p->window->x && y < p->window->y)
	{
		p->texpt.y = abs((((y * 256 - p->window->y * 128 + p->sHeight * 128) * 64)
					/ p->sHeight) / 256);
		ft_memcpy((void*)p->frameptr + 4 * p->window->x * y + x * 4,
				&p->tex[4].ptr[p->texpt.y % 64 * p->tex[4].size_line +
				p->texpt.x % 64 * p->tex[4].bpp / 8], sizeof(int));
	}
}

void sprite_height(t_param *p, int index)
{
	p->sHeight = I(p->window->y / p->sprites[index]->dist);
	p->sTop = -p->sHeight / 2 + p->window->y /2;
	p->sTop = (p->sTop < 0) ? 0 : p->sTop;
	p->sBot = p->sHeight / 2 + p->window->y /2;
	p->sBot = (p->sBot < 0) ? 0 : p->sBot;
}

void sprite_x(t_param *p, int i)
{
  if (p->sprites[i]->side == 0)
    p->x_sprite = p->sprites[i]->raypos.y + p->sprites[i]->dist * p->raydir.y;
  else
    p->x_sprite = p->sprites[i]->raypos.x + p->sprites[i]->dist * p->raydir.x;

  p->texpt.x = I(p->x_sprite * FT(64));

  if (p->sprites[i]->side == 0 && p->raydir.x > 0)
    p->texpt.x = 64 - p->texpt.x - 1;
  if (p->sprites[i]->side == 1 && p->raydir.y < 0)
    p->texpt.x = 64 - p->texpt.x - 1;
  p->texpt.x = abs(p->texpt.x);
}

void draw_sprites(t_param *p)
{
  int i;

  i = 0;
  while (i < p->spritesnb)
  {
    sprite_x(p, i);
    sprite_height(p, i);
    while (++p->sTop <= p->sBot)
      sprite_to_frame(p->x, p->sTop, p),
    i++;
  }
  free_sprites(p);
}
