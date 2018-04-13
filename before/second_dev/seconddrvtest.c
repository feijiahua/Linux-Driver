#include <stdio.h>
#include <fcntl.h>

/*
*firstdrvtest on
*firstdrvtest off
 */

int main(int argc, char *argv[])
{
	int fd;
	unsigned char key_vals[4];

	fd = open("/dev/buttons", O_RDWR);
	if (fd < 0)
	{
		printf("can't open\n");
		return -1;
	}

	while(1)
	{
		read(fd, key_vals, sizeof(key_vals));

	}
	read(fd, 4);

	if (!key_vals[0] || !key_vals[1] || !key_vals[2] || !key_vals[3])
	{
		printk("Key push\n");
	}

	return 0;
}