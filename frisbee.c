#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"
struct lock_t *lock;
static int totalrounds =0;
static int threadnumber;
static int passes;
static int currpid=0;
void* passprintfunction();
int main ( int argc , char * argv [])
{
	threadnumber =atoi(argv[1]);// first argument passed by user when frisbee.c runs
	passes = atoi(argv[2]); // second argument passed by user when frisbee.c runs
	int i = 0 ;
	lock_init(lock);
	for(i=0;i<threadnumber;i++)
	{
		thread_create(passprintfunction,(void *)i); //trigger thread creation
	}
	// sleep();

	wait();
	printf(1,"Simulation of Frisbee game has finished, %d rounds were played in total!",totalrounds);
	sleep(10000);
	exit();
}
/* 
->The passprintfunction here will print the totalrounds of the passes and this function will be fed
  to thread_create routine everytime it runs
->The arg parameter fed to passprintfunction via running of frisbee.c will act as an id for every thread
->During every iteration in while loop, thread will acquire lock and we will further check for certain conditions*/
void* passprintfunction(void *arg)
{
	int pidnum = (int)arg; 
	while(totalrounds<passes)
	{
		lock_acquire(lock);
		if(totalrounds==passes)
			{
			lock_release(lock);		
			break;
			}	
		if(pidnum==currpid)
		{
			totalrounds++;
			printf(1,"Pass number no: %d, Thread %d is passing the token to thread",totalrounds,pidnum);
			currpid++;
			if(currpid ==  threadnumber)
				currpid = 0;	
			printf(1," %d\n",currpid);
			lock_release(lock);		
		 	sleep(2);
		}
		else
		{
			lock_release(lock);		
			sleep(1);
		}
	
	}
	sleep(100);
	// sleep(10000);
	exit();
	
}

