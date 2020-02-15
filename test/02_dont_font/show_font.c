#include <stdio.h>
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
	
	fd_fb = open("/dev/fb0",O_RDWR);
	if(fd_fb < 0)
	{
		printf("can't open /dev/fb0\n");
		return -1;
	}

	/* 获得可变的屏幕信息 */
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


	return 0;
}
