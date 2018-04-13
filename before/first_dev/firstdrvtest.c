#include <stdio.h>
#include <fcntl.h>

/*
*firstdrvtest on
*firstdrvtest off
 */

int main(int argc, char *argv[])
{
	int fd;
	int val = 1;

	fd = open("/dev/xyz", O_RDWR);
	if (fd < 0)
	{
		printf("can't open\n");
		return -1;
	}

	if (argc != 2)
	{
		printf("Usage:\n");
		printf("%s <on|off>", argv[0]);
		return 0;
	}

	if (strcmp(argv[1], "on") == 0)
	{
		val = 1;
	}
	else
	{
		val = 0;
	}
	write(fd, &val, 4);

	return 0;
}