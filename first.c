#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include"semaphore.c"
#include"signal.h"
#include"uses.h"
enum Direction {down,up}; //确定方向

int main(void) {
	floor_first();
	return 0;
}
