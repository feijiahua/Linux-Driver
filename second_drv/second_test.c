#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int fd, i;
	char *filename;
	unsigned char key_val[4] = {0};

	filename = argv[1];

	fd = open(filename, O_RDWR);
	if (fd < 0)
	{
		printf("error, %d\n", fd);
		return -1;
	}

	printf("%d\n",read(fd, key_val, sizeof(key_val)));

	for (i = 0; i < 4; i++)
	{
		printf("%x ", key_val[i]);
	}
	printf("\n");
	return 0;
}