#include <stdio.h>
#include <sys/mman.h>

int main(int argc,char *argv[])
{
	int fd_fb;
	struct fb_var_screeninfo var;	/* Current var */
	struct fb_fix_screeninfo fix;		/* Current fix */
	int screen_size;
	unsigned char *fbmem;
	
	fd_fb = open("/dev/fb0",O_RDWR);
	if(fd_fb < 0)
	{
		printf("open /dev/fb0 error");
		return -1;
	}

	if(ioctl(fd_fb, FBIOGET_VSCREENINFO,&var))
	{
		printf("cannot get var\n");
		return -1;
	}
	
	if(ioctl(fd_fb, FBIOGET_FSCREENINFO,&fix))
	{
		printf("cannot get fix\n");
		return -1;
	}

	/*
	* bits_per_pixel 表示每个像素占据多少位
	*/
	screen_size = var.xres * var.yres * var. bits_per_pixel  / 8;

	fbmem = mmap(NULL, screen_size, );

	
	

	return 0;
}
