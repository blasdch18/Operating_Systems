/* Filename: shm_read_cntr.c */
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

#define SHM_KEY 0x12345

struct shmseg {         
   int par;            
   int impar; 
   int buffer[1024];   
};

int main(int argc, char *argv[]) {
   int shmid, numtimes;
   struct shmseg *shmp;
   int total_count;
   int cntr;
   int sleep_time;
   char *shm ,*s;
  
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }
   // Attach to the segment to get a pointer to it.
   shmp = shmat(shmid, NULL, 0);
   
   if (shmp == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }
   
   /* Read the shared memory cntr and print it on standard output */
   while (shmp->impar != 1) {

      //printf(" %ls \n", shmp->buffer );
      if (shmp->par == -1) {
         perror("read");
         return 1;
      }
      printf("Reading Process: Shared Memory: Read %d \n", shmp->par);
      //printf("Reading Process: Shared Memory: Read %d \n", shmp->impar);
      sleep(1.5);
   }
 
   printf("Reading Process: Reading Done, Detaching Shared Memory\n");
   //shmp->read_complete = 1;
   //printf("value put on shared memory: %s\n", shm);  
   
   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }
   printf("Reading Process: Complete\n");
   return 0;
}