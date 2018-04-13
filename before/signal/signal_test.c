#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/poll.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>

int fd;

void my_signal_fun(int signum)
{
    unsigned char key_val = 0x00;

    read(fd, &key_val, 1);
    printf("key_val = 0x%x\n", key_val);
}

int main(int argc, char **argv)
{
    unsigned char key_val;
    int ret;
    int oflag;

    signal(SIGIO, my_signal_fun);

    fd = open("/dev/button0", 0);
    if (fd < 0)
    {
        printf("can't open\n");
    }

    fcntl(fd, F_SETOWN, getpid()); /* 告诉驱动程序进程id号，用于后续驱动程序发送信号 */
    oflag = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, oflag | FASYNC); /* 设置为异步通知 */

    while(1)
    {
       sleep(1000);
    }

    return 0;    
}

