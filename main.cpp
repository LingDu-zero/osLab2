#include "os2_new.h"


enum Direction { down, up };
#define NULL 0
int main()
{
	sharememoryget();
	char *argc_floor_1[] = { "test","floor_1",NULL}, *argc_floor_2[] = { "test","floor_2",NULL }, *argc_floor_3[] = { "test","floor_3",NULL };
	Direction floor_1, floor_2, floor_3, direction_now;
	int floor_now = 1,elevtor_control=1;
	int mepty = 1;//以上是共享内存区--不同的文件可以改变其读写权限 其余文件只需要在这里读取即可
	create(*argc_floor_1[]);
	create(*argc_floor_2[]);
	create(*argc_floor_3[]);//这里创立各进程
	while (1)
	{
		
	}//这里为所有信息处理中心
	return 0;
}

