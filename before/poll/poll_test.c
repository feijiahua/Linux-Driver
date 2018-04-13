#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/poll.h>

int main(int argc, char **argv)
{
    unsigned char key_val;
    int ret;
    int fd;
    int press_cnt[4];
    struct pollfd fds[1];

    fd = open("/dev/button0", 0);
    if (fd < 0)
    {
        printf("can't open\n");
    }

    fds[0].fd = fd;
    fds[0].events = POLLIN;

    while(1)
    {
        ret = poll(fds, 1, 10000);    /* 等待1s */
        if (ret > 0)
        {
            read(fd, &key_val, 1);
            printf("key_val = %x\n", key_val);
        }
        else
        {
            printf("No key pressed, time out\n");
        }
    }

    return 0;    
}

