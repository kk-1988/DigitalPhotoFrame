#include <stdio.h>
#include <sys/mman.h>
#include <linux/fb.h>

/*
* 提前知道：
* 1.lcd 每个像素占多少位
* 2.屏幕的x,y坐标
* 3.分辨率多少等需要提前知道
*/
int main(int argc,char *argv[])
{
	int fd_fb;
	
	/* 可变信息 */
	struct fb_var_screeninfo var;
	/* 固定信息 */
	struct fb_fix_screeninfo fix;
	int screen_size;
	unsigned char *p_fb_mem = NULL;
	
	fd_fb = open("/dev/fb0",O_RDWR);
	if(fd_fb < 0)
	{
		printf("can't open /dev/fb0\n");
		return -1;
	}

	/* 获得可变的屏幕信息,获取x，y(可见分辨率)，每个像素用多少位等信息 */
	if(ioctl(fd_fb,FBIOGET_VSCREENINFO,&var))
	{
		printf("can't get FBIOGET_VSCREENINFO\n");
		return -1;
	}

	/* 获取固定的屏幕信息 */
	if(ioctl(fd_fb,FBIOGET_FSCREENINFO,&fix))
	{
		printf("can't get FBIOGET_FSCREENINFO\n");
		return -1;
	} 

	/* 1.占用的像素大小(多少个字节) */
	screen_size = var.xres * var.yres * var.bits_per_pixel / 8;

	/* 
	*2. mmap映射 
	*param 说明:
	*void *addr: NULL=>让系统给我们分配虚拟内存地址
	*size:分配的虚拟内存大小
	*prot:属性，可读可写
	*flag：shared
	*fd: fd
	*offset:0
	*/
	p_fb_mem = mmap(NULL, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
	if((signed char *)-1 == p_fb_mem)
	{
		printf("can't mmap fb mem\n");
		return -1;
	}

	/* 显示 */
	lcd_put_ascii();

	return 0;
}
