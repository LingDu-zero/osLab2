#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

enum Direction {down,up}; //确定方向
pthread_t thread[3];  //线程（测试ing）

void display(int floor, Direction drc); //显示电梯运行状态
Direction floor_first();  //接收一层方向信号
Direction floor_second(); //接收二层方向信号
Direction floor_third(); //接收三层方向信号
int lift_floor(); //接收电梯内部去往层数
bool lift_switch(); //接收电梯的开与关

void display(int floor, Direction drc) {
	if (drc == down)
		printf("In the %d floor and go down\n", floor);
	else if (drc == up)
		printf("In the %d floor and go up\n", floor);
	else
		printf("error in display");
}

Direction floor_first() {
	char a;
	printf("you'r in the first floor, do you want to go up(y/n)?\n");
	scanf_s("%c", &a);
	if (a == 'y')
		return up;
}

Direction floor_second() {
	char a;
	printf("you'r in the second floor, do you want to go up or down(u/d)?\n");
	scanf_s("%c", &a);
	if (a == 'u')
		return up;
	else if (a == 'd')
		return down;
}

Direction floor_third() {
	char a;
	printf("you'r in the second floor, do you want to go down(y/n)?\n");
	scanf_s("%c", &a);
	if (a == 'y')
		return down;
}

int lift_floor() {
	int lift_floor;
	printf("How many floors do you want to(1/2/3)?");
	scanf_s("%d", &lift_floor);
	return lift_floor;
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
	while (true) {
		while (s = _kbhit()) {
			switch (s) {
			case'1':d = floor_first(); break;
			case'2':d = floor_second(); break;
			case'3':d = floor_third(); break;
			default:continue;
			}
		}
	}

	system("pause");
	return 0;
}
