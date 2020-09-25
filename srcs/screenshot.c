#include "../includes/cub3d.h"

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define BPP 3

void shift(unsigned char *headers, int value)
{
  headers[0] = UC (value);
  headers[1] = UC (value >> 8);
  headers[2] = UC (value >> 16);
  headers[3] = UC (value >> 24);
}

void writeHeader(int fd, t_param *p, int size)
{
  unsigned  char  headers[54];
  int             i;
  i = 0;
  while(i < 54)
    headers[i++] = UC 0;
  headers[0] = UC'B';
  headers[1] = UC'M';
  shift(headers + 2, size);
  headers[10] = UC 54;
  headers[14] = UC 40;
  shift(headers + 18, p->window->x);
  shift(headers + 22, p->window->y);
  headers[27] = UC 1;
  headers[28] = UC 24;

  write(fd, headers, 54);
}

int writeColors(int fd, t_param *p)
{
  unsigned char	rgb[3] = {
		0, 0, 0 };
	int						i;
	int						j;
  t_pt          dim;

  i = 0;
  dim.x = p->window->x;
  dim.y = p->window->y-1;
	while (i < p->window->y)
	{
		j = 0;
		while (j < p->window->x)
		{
			rgb[0] = ((p->frameptr[(dim.y - i) * dim.x + j]) >> 16);
			rgb[1] = ((p->frameptr[(dim.y - i) * dim.x + j]) >> 8);
			rgb[2] = (p->frameptr[(dim.y - i) * dim.x + j]);
			if ((write(fd, rgb + 2, 1)) < 0)
				return (0);
			if ((write(fd, rgb + 1, 1)) < 0)
				return (0);
			if ((write(fd, rgb, 1)) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);

}

void writeImage(t_param *p)
{
        int outputFd;
        int fileSize;
        //int bytes;

        fileSize = 54 + (p->window->x * p->window->y);
        if(!(outputFd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777)))
          printf("couldn't create bmp\n");

        writeHeader(outputFd, p, fileSize);
        writeColors(outputFd, p);
        close(outputFd);
}

void screenshot(char **argv, t_param  *p)
{
  int fd;

  if (!(fd = open(argv[1], O_RDONLY)))
    exit(2);
  if (!(check_and_parse(argv, fd, p)))
  {
    printf("invalid .cub file");
    exit (2);
  }
  single_ray_cast(p);
  writeImage(p);
  free_and_exit(p);
}
