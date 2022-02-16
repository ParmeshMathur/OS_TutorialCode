#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#include<asm/unistd.h>

int sum;
void *runner(void *param);
int main(int argc,char *argv[])
{ 
	printf("Main Thread:The pid is %d\n",getpid());
	printf("Main thread:The tid is %lu\n",pthread_self());

	pthread_t tid1, tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid1,&attr, runner, argv[1]);
	pthread_create(&tid2,&attr, runner, argv[2]);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("Main: sum= %d\n",sum);
}

void *runner ( void *param )
{ 
	int upper=atoi(param);
	int i; sum;
	printf("New Thread: The pid is %d\n",getpid());
	printf("New Thread: The real pid is %lu\n",syscall(__NR_gettid));
	printf("New Thread: The tid is %lu\n",pthread_self());

	if (upper>0)
	{ 
		for ( i=1; i <= upper; i++ )
		{ sum = sum + i; } 
	}
	printf("New Thread: sum = %d\n",sum);
	pthread_exit(0);
}