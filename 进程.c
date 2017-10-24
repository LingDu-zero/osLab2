#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

enum Direction { down, up }; //确定方向
pthread_t thread[3];  //线程（测试ing）

void display(int floor, Direction drc); //显示电梯运行状态
Direction floor_first();  //接收一层方向信号
Direction floor_second(); //接收二层方向信号
Direction floor_third(); //接收三层方向信号
int lift_floor(); //接收电梯内部去往层数
bool lift_switch(); //接收电梯的开与关

bool firstfloor_put_key;
bool secondfloor_put_key;
bool thirdloor_put_key;

int S0 = 1;//电梯门是否开,初值为1，表示可以进人
int S1 = 0;//一楼是否有人
int S2 = 0;//二楼是否有人
int S3 = 0;//三楼是否有人

int main(void)
{

	cobegin

		lift();      	 /*电梯本身进程*/
	lift_ctr();   	 /*电梯控制面板进程*/
	firstFloor_ctr();   /*第一层控制面板进程*/
	secondFloor_ctr();   /*第二层控制面板进程*/
	thirdFloor_ctr();    /*第三层控制面板进程*/


	coend
}

		lift() {
			while (true) {
				P(S0);		//电梯可载人
				P(S1);		//一楼是否有人等电梯

				P(S2);		//二楼是否有人等电梯


				P(S3);		//三楼是否有人等电梯

			}
		}


		lift_ctr() {
			while (true)
			{
				P(S0);			//电梯门开着，则控制面板被挂起
				aim_floor() = 1;
		    	//aim_floor() = 2;
				//aim_floor() = 3;
				V(S0);
			}
			

		}


		firstFloor_ctr()   /*第一层控制面板进程*/
		{
			while (true) {
				P(S0);		//电梯是否打开
				if (firstfloor_put_key == 1)V(S1);//一楼按下按键,说明有人在等电梯
				floor_first() = up;
				V(S0); //电梯关门，继续服务
			}
		}

		secondFloor_ctr()  /*第二层控制面板进程*/
		{
			while (true) {
				P(S0);		//电梯是否打开
				if (secondfloor_put_key == 1)V(S2);//二楼按下按键,说明有人在等电梯
				second_first() = up/down;
				V(S0); //电梯关门，继续服务
			}	
		}


		thirdFloor_ctr()  /*第三层控制面板进程*/
		{
			while (true) {
				P(S0);		//电梯是否打开
				if (secondfloor_put_key == 1)V(S3);//三楼按下按键,说明有人在等电梯
				third_first() = up / down;
				V(S0); //电梯关门，继续服务
			}
		
		}
