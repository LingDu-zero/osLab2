#include"os2_new.h"

int main()
{
	sharememoryget();
	Direction floor_1;
	int floor_now;
	while (1)
	{
		printf("this is the direcion:\n");
		if (floor_1 == up)
		{
			printf("up");
		}
		else if (floor_1 == down)
		{
			printf("down");
		}
		else
		{
			printf("NULL");
		}
		printf("the is the floor number now: %d\t", floor_now);
	}
	return 0;
}
