#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <pthread.h>

enum Direction {down,up};
pthread_t thread[3];

void display(int floor, Direction drc);
Direction floor_first();
Direction floor_second();
Direction floor_third();
int lift_floor();
bool lift_switch();

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

bool lift_switch() {

}

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

int main(void) {
	char s;
	Direction d;
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
