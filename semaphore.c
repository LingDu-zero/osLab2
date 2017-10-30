#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
 
/*联合体变量*/
union semun
{
 int val; //信号量初始值                   
 struct semid_ds *buf;        
 unsigned short int *array;  
 struct seminfo *__buf;      
};
 
/*函数声明，信号量定义*/

static void P(int sem_d);  //执行P操作
static void V(int sem_d);  //执行V操作
static int sem_id = semget(IPC_PRIVATE, 1, 0666);           //信号量标识符
 

//op是-1那么p操作,op是1那么v操作
/*
void pv(int sem_id, int op)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = op;
	sem_b.sem_flg = SEM_UNDO;
	semop(sem_id, &sem_b, 1);
}
*/

void P(int sem_d) {
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	semop(sem_id, &sem_b, 1);
}

void V(int sem_d) {
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	semop(sem_id, &sem_b, 1);
}

/*
union semun sem_un;
sem_un.val = 1;
semctl(sem_id, 0, SETVAL, sem_un);
*/


	



