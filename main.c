#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

enum Direction {down,up}; //确定方向
pthread_t thread[3];  //线程（测试ing）

void display(int floor, Direction drc); //用于响应有人等待后信息展示
bool isPerson();// 判断是否有人等待
Direction isDirection();//用于第二层人判断方向
int isFloor(int now_floor);//用于电梯面板内层数选择

bool lift_switch(); //接收电梯的开与关

void display(int floor, Direction drc) {
	if (drc == down)
		printf("%d floor is waiting, %c\n", floor, 25);
	else if (drc == up)
		printf("%d floor is waiting, %c\n", floor, 24);
}

bool isPerson() {
	srand(unsigned(time(NULL)));
	int r = rand() % 10;
	if (r > 6)
		return true;
	else
		return false;
}

Direction isDirection() {
	srand(unsigned(time(NULL)));
	Direction r = Direction(rand() % 2);
	return r;
}

int isFloor(int now_floor) {
	srand(unsigned(time(NULL)));
	int r;
	while (now_floor == (r = rand() % 3 + 1));
	return r;
}

//暂时不写
bool lift_switch() {

}

//线程均在测试中
/***
void *thread1() {
	const int floor = 1;
	display(floor, up);
	floor_first();
}

void *thread1() {
	const int floor = 2;
	display(floor, up);
	floor_first();
}

void *thread1() {
	const int floor = 3;
	display(floor, up);
	floor_first();
}

void thread_create() {

}
***/

int create(int floor_number_or_control)
{
	pid_t floor_number_or_control = fork();
	printf(floor_number_or_control 'pid is == %d/n', getpid());
	return 0;
}
//建立多个进程，进程部分应该在window无法运行，可以在linux尝试发
//这里只是加入创立函数，各进程功能未划分

int main(void) {
	char s;
	Direction d;
	create(floor_first);
	create(floor_second);
	create(floor_third);
	create(control);

	system("pause");
	return 0;
}
