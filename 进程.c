#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

enum Direction { down, up }; //ȷ������
pthread_t thread[3];  //�̣߳�����ing��

void display(int floor, Direction drc); //��ʾ��������״̬
Direction floor_first();  //����һ�㷽���ź�
Direction floor_second(); //���ն��㷽���ź�
Direction floor_third(); //�������㷽���ź�
int lift_floor(); //���յ����ڲ�ȥ������
bool lift_switch(); //���յ��ݵĿ����

bool firstfloor_put_key;
bool secondfloor_put_key;
bool thirdloor_put_key;

int S0 = 1;//�������Ƿ�,��ֵΪ1����ʾ���Խ���
int S1 = 0;//һ¥�Ƿ�����
int S2 = 0;//��¥�Ƿ�����
int S3 = 0;//��¥�Ƿ�����

int main(void)
{

	cobegin

		lift();      	 /*���ݱ������*/
	lift_ctr();   	 /*���ݿ���������*/
	firstFloor_ctr();   /*��һ�����������*/
	secondFloor_ctr();   /*�ڶ������������*/
	thirdFloor_ctr();    /*���������������*/


	coend
}

		lift() {
			while (true) {
				P(S0);		//���ݿ�����
				P(S1);		//һ¥�Ƿ����˵ȵ���

				P(S2);		//��¥�Ƿ����˵ȵ���


				P(S3);		//��¥�Ƿ����˵ȵ���

			}
		}


		lift_ctr() {
			while (true)
			{
				P(S0);			//�����ſ��ţ��������屻����
				aim_floor() = 1;
		    	//aim_floor() = 2;
				//aim_floor() = 3;
				V(S0);
			}
			

		}


		firstFloor_ctr()   /*��һ�����������*/
		{
			while (true) {
				P(S0);		//�����Ƿ��
				if (firstfloor_put_key == 1)V(S1);//һ¥���°���,˵�������ڵȵ���
				floor_first() = up;
				V(S0); //���ݹ��ţ���������
			}
		}

		secondFloor_ctr()  /*�ڶ������������*/
		{
			while (true) {
				P(S0);		//�����Ƿ��
				if (secondfloor_put_key == 1)V(S2);//��¥���°���,˵�������ڵȵ���
				second_first() = up/down;
				V(S0); //���ݹ��ţ���������
			}	
		}


		thirdFloor_ctr()  /*���������������*/
		{
			while (true) {
				P(S0);		//�����Ƿ��
				if (secondfloor_put_key == 1)V(S3);//��¥���°���,˵�������ڵȵ���
				third_first() = up / down;
				V(S0); //���ݹ��ţ���������
			}
		
		}
