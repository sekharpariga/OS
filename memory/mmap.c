#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PAGE_SIZE 1024

long file_size (char * file_name)
{
	struct stat sFile;
	int rc = stat(file_name,&sFile);
	return rc == 0 ? sFile.st_size : -1;
}

int main(int argc, char* argv[])
{
	long size = file_size(argv[1]);
	printf("file size : %ld\n", size);

	int fd = open(argv[1], O_RDONLY);
	printf("file open fd : %d\n", fd);

	char *pmmap = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);

	if(pmmap == MAP_FAILED)
	{
		perror("Memory allocation is failed\n");
		return 1;
	}

	printf("%s\n",pmmap);

	// for(long i = 0; i < size; i++)
	// {
	// 	printf("%c", *(pmmap + i));
	// }

	close(fd);
	return 0;
}