#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
enum Direction { down, up }; //确定方向
int create(char *argc[])
{
	char *arg[] = { "ls","-l",NULL };
	if (fork() == 0)
	{
		printf("execl...\n");
		if (execl(argc, NULL)<0)
		{
			fprintf(stderr, "execl failed:%s", strerror(errno));
			return -1;
		}
	}
	printf("the process is over");
	return 0;
}

void sharememoryget()
{
	shmget(1, 256, 0777);
}
