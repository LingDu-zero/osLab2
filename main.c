#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

enum Direction {down,up}; //确定方向

void display(int floor, Direction drc); //用于响应有人等待后信息展示
bool isPerson();// 判断是否有人等待
Direction isDirection();//用于第二层人判断方向
int isFloor(int now_floor);//用于电梯面板内层数选择
process floor_first();//进程一层
process floor_seconde();//进程二层
process floor_third();//进程三层

bool lift_switch(); //接收电梯的开与关

process floor_fisrt() {
	semaphore person = 0;//信号量Person判断是否有人
	while (true) {
		if (person == 0) {
			if (isPerson()) {
				P(person);//有人则增加，人进电梯后V(Person)，进程通信
				/***
				临界区
				***/
				display(1, up);
			}
		}
		else if (person == 1)
			display(1, up);
		else
			printf("1 floor person error\n");
		sleep(1);
	}
}

process floor_second() {
	Direction drc;
	semaphore u = 0;
	semaphore d = 0;
	while (true) {
		if (isPerson()) {
			drc = isDirection();
			if (drc == up) {
				if (u == 0) {
					P(u);
					display(2, up);
					/***
					临界区
					***/
				}
				else
					display(2, up);
			}
			else if (drc == down) {
				if (d == 0) {
					P(d);
					display(2, down);
					/***
					临界区
					***/
				}
				else
					display(2, down);
			}
		}
		sleep(1);
	}
}

process floor_third() {
	semaphore person = 0;
	while (true) {
		if (person == 0) {
			if (isPerson()) {
				P(person);
				/***
				临界区
				***/
				display(3, down);
			}
		}
		else if (person == 1)
			display(3, down);
		else
			printf("3 floor person error\n");
		sleep(1);
	}
}

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
