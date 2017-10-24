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
static int set_semvalue(void); //设置信号量
static void del_semvalue(void);//删除信号量
static int semaphore_p(void);  //执行P操作
static int semaphore_v(void);  //执行V操作
static int sem_id;             //信号量标识符
 
int main(int argc, char *argv[])
{
 int i;
 int pause_time;
 char op_char = 'O';
 srand((unsigned int)getpid());  
 sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);//创建一个信号量,IPC_CREAT表示创建一个新的信号量
 
 /*如果有参数，设置信号量，修改字符*/
 if (argc > 1) 
 {
  if (!set_semvalue()) 
  {
   fprintf(stderr, "Failed to initialize semaphore/n");
   exit(EXIT_FAILURE);
  }
  op_char = 'X';
  sleep(5);
 }
 for(i = 0; i < 10; i++)  
 {      

  /*执行P操作*/
  if (!semaphore_p()) 
   exit(EXIT_FAILURE);
  printf("%c", op_char);
  fflush(stdout);
  pause_time = rand() % 3;
  sleep(pause_time);
  printf("%c", op_char);
  fflush(stdout);
 
  /*执行V操作*/
  if (!semaphore_v()) 
   exit(EXIT_FAILURE);
  pause_time = rand() % 2;
  sleep(pause_time);
 }   
 printf("/n%d - finished/n", getpid());
 if (argc > 1) 
 {    
  sleep(10);
  del_semvalue(); //删除信号量
 }    
 exit(EXIT_SUCCESS);
}
 
/*设置信号量*/
static int set_semvalue(void)
{
 union semun sem_union;
 sem_union.val = 1;
 if (semctl(sem_id, 0, SETVAL, sem_union) == -1) 
  return(0);
 
 return(1);
}
 
/*删除信号量*/
static void del_semvalue(void)
{
 union semun sem_union;  
 if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
  fprintf(stderr, "Failed to delete semaphore/n");
}
 
/*执行P操作*/
static int semaphore_p(void)
{
 struct sembuf sem_b;   
 sem_b.sem_num = 0;
 sem_b.sem_op = -1; /* P() */
 sem_b.sem_flg = SEM_UNDO;
 if (semop(sem_id, &sem_b, 1) == -1) 
 {
  fprintf(stderr, "semaphore_p failed/n");
  return(0);
 }
 return(1);
}

/*执行V操作*/
static int semaphore_v(void)
{
 struct sembuf sem_b;
 sem_b.sem_num = 0;
 sem_b.sem_op = 1; /* V() */
 sem_b.sem_flg = SEM_UNDO;
 if (semop(sem_id, &sem_b, 1) == -1) 
 {
  fprintf(stderr, "semaphore_v failed/n");
  return(0);
 }
 return(1);
}