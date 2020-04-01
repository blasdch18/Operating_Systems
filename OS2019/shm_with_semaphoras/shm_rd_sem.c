/* Filename: shm_read_cntr.c */
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

#define SHM_KEY 0x12345
#define SEM_KEY 0x54321

struct shmseg {         
   int par;            
   int impar; 
   int buffer;   
};

int main(int argc, char *argv[]) {
   int shmid, numtimes;
   struct shmseg *shmp;
   int total_count;
   int cntr;
   int sleep_time;
   char *shm ,*s;

   struct sembuf sem_buf;
   struct semid_ds buf;
   int semid;
   int retval;


  
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
   
    /* Got the semaphore */
   if (semid >= 0) {
      printf("First Process\n");
      sem_buf.sem_op = 1;
      sem_buf.sem_flg = 0;
      sem_buf.sem_num = 0;
      retval = semop(semid, &sem_buf, 1);
      if (retval == -1) {
         perror("Semaphore Operation: ");
         //return;
      }
   } else if (errno == EEXIST) { // Already other process got it
      int ready = 0;
      printf("Second Process\n");
      semid = semget(SEM_KEY, 1, 0);
      if (semid < 0) {
         perror("Semaphore GET: ");
         //return;
      }
      
      /* Waiting for the resource */
      sem_buf.sem_num = 0;
      sem_buf.sem_op = 0;
      sem_buf.sem_flg = SEM_UNDO;
      retval = semop(semid, &sem_buf, 1);
      if (retval == -1) {
         perror("Semaphore Locked: ");
         //return;
      }
   }
   sem_buf.sem_num = 0;
   sem_buf.sem_op = -1; /* Allocating the resources */
   sem_buf.sem_flg = SEM_UNDO;
   retval = semop(semid, &sem_buf, 1);
   
   if (retval == -1) {
      perror("Semaphore Locked: ");
      //return;
   }

   /* Read the shared memory cntr and print it on standard output */
   while (shmp->impar != 1) {

      //printf(" %ls \n", shmp->buffer );
      if (shmp->par == -1) {
         perror("read");
         return 1;
      }
      printf("Reading Process: Shared Memory: Read  ");
      //printf("Reading Process: Shared Memory: Read %d \n", shmp->impar);
      if(shmp->buffer % 2==0){
      	printf("%d      <<<<<   Par \n", shmp->par );
      }else{
      	printf("%d                  <<<<<   ImPar \n", shmp->impar);
      }
      sleep(1.5);
   }
 
   printf("Reading Process: Reading Done, Detaching Shared Memory\n");
   //shmp->read_complete = 1;
   //printf("value put on shared memory: %s\n", shm);  
   
   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }

	sem_buf.sem_op = 1; /* Releasing the resource */
   	retval = semop(semid, &sem_buf, 1);
   
   if (retval == -1) {
      perror("Semaphore Locked\n");
      //return;
   }




   printf("Reading Process: Complete\n");
   return 0;
}