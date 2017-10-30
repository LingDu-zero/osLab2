#ifndef _SHMDATA_H_HEADER  
#define _SHMDATA_H_HEADER  
#include <semaphore.h>
#define SIZE 2048  

enum Direction {down,up};
struct shared_use_st  
{  
	semaphore signal=0;
	semaphore mutex=1;
	semaphore panel=0;
	int now_floor=1;
	int aim_floor;
	int aim_floor_panel;
	bool up[3] = {false};
	bool down[3] = {false};
	bool signal[3] = {false};
	Direction drc;
};  
      
#endif  
