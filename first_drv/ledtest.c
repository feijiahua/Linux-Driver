#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/* /dev/led on */
int main(int argc, char **argv)
{
	int fd;
	char *filename;
	char val;

	filename = argv[1];

	fd = open(filename, O_RDWR);
	if (fd < 0)
	{
		printf("error,%d\n", fd);
		return -1;
	}

	if (!strcmp("on", argv[2]))
	{
		val = 0;
		write(fd, &val, 1);
	}
	else if (!strcmp("off", argv[2]))
	{
		val = 1;
		write(fd, &val, 1);
	}
	else
	{
		printf("input error\n");
	}

	read(fd, &val, 1);
    printf("%x\n", val);

	return 0;
}