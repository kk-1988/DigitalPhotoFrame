#include <stdio.h>

int main(int argc,char *argv[])
{	
	int i = 0;
	unsigned char *str = "abc中";
	
	while(str[i])
	{
		printf("%02x",str[i]);
		i++;	
	}

	
	return 0;
}