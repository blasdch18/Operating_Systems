#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NITERS	1000000

void *Count(void *argp);

sem_t	sem;
unsigned int	cnt = 1;
unsigned int tem;

int main(void)
{
	pthread_t	tid1,tid2,tid3;

	sem_init(&sem,0,1);

	 if(pthread_create(&tid1, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

   if(pthread_create(&tid2, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

   if(pthread_create(&tid3, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    } 

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if (cnt < 2 * NITERS) 
        printf("\n BOOM! cnt is [%d], should be %d\n", cnt, 2*NITERS);
    else
        printf("\n OK! cnt is [%d]\n", cnt);
  
    pthread_exit(NULL);


}

void *Count(void *argp)
{
	int	i;
	for (i = 0;i < NITERS;i ++){
		sem_wait(&sem);
    tem=cnt;
		cnt = cnt*2;
    printf("el anterior es :%d el nuevo valor es :%d\n",tem,cnt );

		sem_post(&sem);
	}
	return NULL;
}
