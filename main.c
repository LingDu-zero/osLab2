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
process lift_panel();//进程电梯面板
process lift();//进程电梯运行

bool lift_switch(); //接收电梯的开与关

semaphore signal=0;
semaphore mutex=1;
semaphore panel=0;

bool up[3] = {false};
bool down[3] = {false};
bool signal[3] = {false};

process lift(){
	int now_floor=1;
	int aim_floor;
	int i=0;
	while(true){
		P(signal);//先判断是否有信号，没有则睡眠
		P(mutex);
		while(!signal[i++]);
		aim_floor = i;//提取有信号的项
		if(aim_floor > now_floor)
			while(aim_floor!=now_floor){
				now_floor++;
				sleep(1);
				//判断当前楼层是否有信号以及是否同向
				if(up[now_floor]){
					lift_open();
					sleep(1);
					V(panel);
					sleep(1);
				}
			}		
		else if(aim_floor<now_floor)
			while(aim_floor!=now_floor){
				now_floor--;
				sleep(1);
				//判断当前楼层是否有信号以及是否同向
				if(down[now_floor]){
					lift_open();
					sleep(1);
					V(panel);
					sleep(1);
				}
			}
		
	}
}

process lift_panel(){
	int aim_floor_panel;
	while (true) {
		P(panel);//控制panel进程睡眠
		aim_floor_panel = isFloor();
		signal[aim_floor_panel] = true;
	}
}

process floor_fisrt() {
	semaphore person_1 = 0;//信号量Person判断是否有人
	while (true) {
		if (person_1 == 0) {
			if (isPerson()) {
				P(person_1);//有人则增加，人进电梯后V(Person)，进程通信
				/***
				临界区
				***/
				display(1, up);
			}
		}
		else if (person_1 == 1)
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
	semaphore person_2 = 0;
	while (true) {
		if (person_2 == 0) {
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
