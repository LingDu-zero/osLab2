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

void lift(){
	int now_floor=1;
	int aim_floor;
	int i=0;
	while(true){
		P(signal);//先判断是否有信号，没有则睡眠
		for(int i=0;i<3;i++)//提取上行下行中的一个信号作为目标方向
			if(up[i]||down[i]||signal[i]){
				aim_floor=i;
				break;
			}
		if(aim_floor > now_floor)
			while(aim_floor!=now_floor){
				now_floor++;
				sleep(2); //上一层楼2s
				if(up[now_floor]){ //判断当前方向是否存在人
					P(mutex);
					up[now_floor]=false;
					P(signal);
					V(mutex);
					V(panel);//唤醒面板进程确定去向
				}
				if(signal[now_floor]){
					P(mutex);
					signal[now_floor]=false;
					P(signal);
					V(mutex);
				}
				sleep(1);//开门1s
				sleep(1);//关门1s
			}		
		else if(aim_floor<now_floor)
			while(aim_floor!=now_floor){
				now_floor--;
				sleep(2);
				if(down[now_floor]){
					P(mutex);
					down[now_floor]=false;
					P(signal);
					V(mutex);
					V(panel);
				}
				if(signal[now_floor]){
					P(mutex);
					signal[now_floor]=false;
					P(signal);
					V(mutex);
				}
				sleep(1);
				sleep(1);
			}
		else{                       //如果目标层即是当前层，开门
			P(mutex);
			if(up[now_floor])
				up[now_floor]=false;
			else
				down[now_floor]=false;
			V(mutex);
			V(panel);
			sleep(1);
			sleep(1);
		}
	}
}

void lift_panel(){
	int aim_floor_panel;
	while (true) {
		P(panel);//控制panel进程睡眠
		aim_floor_panel = isFloor();
		signal[aim_floor_panel] = true;
	}
}

void floor_fisrt() {
	while (true) {
		if (isPerson()) {
			P(mutex);
			up[1]=true;
			V(signal);
			V(mutex);	
			display(1, up);
		}
		sleep(1);
	}
}

void floor_second() {
	Direction drc;
	while (true) {
		if (isPerson()) {
			drc = isDirection();
			if (drc == up) {
				P(mutex);
				up[2]=true;
				V(signal);
				V(mutex);
				display(2,up);
			}
			else if (drc == down) {
				P(mutex);
				down[2]=true;
				V(signal);
				V(mutex);
				display(2, down);
			}
		}
		sleep(1);
	}
}

void floor_third() {
	while (true) {
		if (isPerson()) {
			P(mutex);
			down[3]=true;
			V(signal);
			V(mutex);	
			display(3, down);
		}
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

void create(int floor_number_or_control)
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
	int floor_first, floor_second, floor_third, lift_panel, lift;

	create(floor_first);
	if (floor_first == 0) {
		process floor_first();//执行进程一层
		return 0;
	}

	create(floor_second);
	if (floor_second == 0) {
		process floor_seconde();//进程二层
		return 0;
	}
	create(floor_third);
	if (floor_third == 0) {
		process floor_third();//进程三层

		return 0;
	}

	create(lift_panel);
	if (lift_panel==0) {
		process lift_panel();//进程电梯面板
	}


	create(lift);
	if (lift == 0) {
		process lift();//进程电梯运行
		return 0;
	}
	system("pause");
	return 0;
}
