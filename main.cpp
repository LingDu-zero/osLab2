#include "os2_new.h"


enum Direction { down, up };
#define NULL 0
int main()
{
	sharememoryget();
	char *argc_floor_1[] = { "test","floor_1",NULL}, *argc_floor_2[] = { "test","floor_2",NULL }, *argc_floor_3[] = { "test","floor_3",NULL };
	Direction floor_1, floor_2, floor_3, direction_now;
	int floor_now = 1,elevtor_control=1;
	int mepty = 1;//�����ǹ����ڴ���--��ͬ���ļ����Ըı����дȨ�� �����ļ�ֻ��Ҫ�������ȡ����
	create(*argc_floor_1[]);
	create(*argc_floor_2[]);
	create(*argc_floor_3[]);//���ﴴ��������
	while (1)
	{
		
	}//����Ϊ������Ϣ��������
	return 0;
}

