#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
    int i;
    int ret;
    int fd;
    int press_cnt[4];
    
    if (2 == argc)
    {
    	fd = open(argv[1], 0);
    	if (fd < 0) 
    	{
	        printf("Can't open /dev/button0\n");
	        return -1;
	    }
        // 这是个无限循环，进程有可能在read函数中休眠，当有按键被按下时，它才返回
    	while (1) 
    	{
	        // 读出按键被按下的次数
	        ret = read(fd, &press_cnt[0], sizeof(press_cnt[0]));
	        if (ret < 0) {
	            printf("read err!\n");
	            continue;
	        } 

        	printf("%d\n", press_cnt[0]);
    	}
    
    	close(fd);
    }
    
    return 0;    
}

