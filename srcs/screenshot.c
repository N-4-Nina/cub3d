#include "../includes/cub3d.h"

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40


void writeHeader(int fd, void *img)
{
  int paddedRowSize;
  unsigned int fileSize;
  unsigned  int dataOffset;
  //*****HEADER************//
  write(fd, "BM", 2);
  paddedRowSize = (int)(4 * ceil((float)width/4.0f))*img->bpp;
  fileSize = paddedRowSize*img->height + HEADER_SIZE + INFO_HEADER_SIZE;
  write(fd, ft_itoa(fileSize), floor(log10(fileSize)) + 1);
  write(fd, "0x0000", 6);
  dataOffset = HEADER_SIZE+INFO_HEADER_SIZE;
  write(fd, ft_itoa(dataOffset), floor(log10(dataOffset)) + 1);
}

void writeInfoHeader(int fd, void *img)
{
  //*******INFO*HEADER******//
  write(fd, ft_itoa(INFO_HEADER_SIZE), 40);
  write(fd, ft_itoa(img->width), floor(log10(abs(img->width))) + 1);
  write(fd, ft_itoa(img->height), floor(log10(abs(img->height))) + 1);
  write(fd, "1", 1);
  write(fd, ft_itoa(img->bpp * 8), floor(log10(abs(img->bpp * 8))) + 1);
}

void writeCompression(int fd, void *img)
{
  //write compression
  int size;
  size = img->width*img->height*img->bpp
  write(fd, "0", 1);
  write(fd, ft_itoa(size), floor(log10(abs(size))) + 1);
  write(fd, "11811", 6);
  write(fd, "11811", 6);
  write(fd, "0", 1);
  write(fd, "0", 1);
}

void writeImage(void *img)
{
        int i;
        int unpaddedRowSize;
        int outputFd;
        int bytes;

        outputFd = open("screenshot.bmp", O_RDWR, O_CREAT);

        writeHeader(outputFd, img);
        writeInfoHeader(outputFd, img);
        writeCompression(outputFd, img);
        i = 0;
        unpaddedRowSize = img->width*img->bpp;
        bytes = img->width*img->height*img->bpp;
        while (i < bytes)
        {
                //int pixelOffset = ((height - i) - 1)*unpaddedRowSize;
                write(outputFd, img->data[i], 4);
                i+= 4;
        }
        close(outputFd);
}

void screenshot(char **argv, t_param  *param)
{
  int fd;

  if (!(fd = open(argv[1], O_RDONLY)))
    exit(2);
  if (!(check_and_parse(argv, fd, param)))
  {
    printf("invalid .cub file");
    exit (2);
  }
  ray_casting(p);
  writeImage(p->frame);
}
