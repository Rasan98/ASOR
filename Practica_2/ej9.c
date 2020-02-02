#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
int main(int argc, char* argv[]){
	struct stat buf;		
	if(stat(argv[1], &buf) == -1){
		perror("stat");
		return -1;
	}

	printf("Major --> %u\n", major(buf.st_dev));
	printf("Minor --> %u\n", minor(buf.st_dev));
	printf("I-node number --> %u\n", buf.st_ino);
	
	switch(buf.st_mode & S_IFMT){
	case S_IFREG:
		printf("File Type --> Regular File\n");
		break;
	case S_IFLNK:
		printf("File Type --> Symbolic link\n");
		break;
	case S_IFDIR:
		printf("File Type --> Directory\n");
		break;
	default:
		printf("File Type --> Unknown\n");
	}

	printf("Last access --> %s\n", ctime(&buf.st_atime));
	return 1;
}
