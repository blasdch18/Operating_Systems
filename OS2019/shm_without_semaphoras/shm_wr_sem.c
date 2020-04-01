/* Filename: shm_write_cntr_with_sem.c */
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define SHM_KEY 0x12345
#define SEM_KEY 0x54321
#define MAX_TRIES 20

struct shmseg {      
   int par;               
   int impar;     
   int buffer[1024];      
};
void shared_memory_par(int, struct shmseg*, int);
void shared_memory_impar(int, struct shmseg*, int);


int main(int argc, char *argv[]) {
   int shmid;
   struct shmseg *shmp;
   char *bufptr;
   //int total_count;
   int sleep_time;
   pid_t pid;
   int initializer;
   if (argc != 2){
      printf("Pares o Impares :");
      return 0;
   }

   else if(argv[1][0]=='p'){
      initializer = 0;
      printf("Pares\n");
   }
   else if(argv[1][0]=='i'){   
      initializer = 1;
      printf("Impares\n");
   }

   //initializer+=2;
   

   printf("Well .. the initializer is %d\n", initializer);
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }
   // Attach to the segment to get a pointer to it.
   shmp = shmat(shmid, NULL, 0);
   
   if (shmp == (void *) -1) {
      perror("Shared memory attach: ");
      return 1;
   }
   shmp->par= initializer;
   //shmp->impar= initializer;
   pid = fork();
   
   /* Parent Process - Writing Once */
   if (pid > 0) {
      shared_memory_par(pid, shmp, initializer);
   } else if (pid == 0) {
      shared_memory_par(pid, shmp, initializer);
      return 0;
   } else {
      perror("Fork Failure\n");
      return 1;
   }
   while (shmp->impar != 1)
   sleep(1);
   
   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }
   
   if (shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
      return 1;
   }
   printf("Writing Process: Complete\n");
   
   return 0;
}

/* Increment the counter of shared memory by total_count in steps of 1 */
void shared_memory_par(int pid, struct shmseg *shmp, int initializer) {
   int cntr;
   int numtimes;
   int sleep_time;
   int semid;
   char bu[20];
   struct sembuf sem_buf;
   struct semid_ds buf;
   int tries;
   int retval;
   semid = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
   //printf("errno is %d and semid is %d\n", errno, semid);
  
   cntr = shmp->par;
   //shmp->write_complete = 0;
   if (pid == 0)
   printf("SHM_WRITE: CHILD: Now writing\n");
   else if (pid > 0)
   printf("SHM_WRITE: PARENT: Now writing\n");
   //printf("SHM_CNTR is %d\n", shmp->cntr);
   
   /* Increment the counter in shared memory by total_count in steps of 1 */
   for (numtimes = 0; numtimes < 1000; numtimes++) {
      cntr += 2;
      shmp->par = cntr;
      printf("Number is %d\n", shmp->par);
      /* Sleeping for a second for every thousand */
      shmp->buffer[numtimes]=cntr; 
      /*
      sleep_time = cntr % 10;
      if (sleep_time == 0)*/
      sleep(4);
   }}
  // shmp->write_complete = 1;

void shared_memory_impar(int pid, struct shmseg *shmp, int initializer) {
   int cntr;
   int numtimes;
   int sleep_time;
   int semid;
   char bu[20];
   struct sembuf sem_buf;
   struct semid_ds buf;
   int tries;
   int retval;
   semid = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
   //printf("errno is %d and semid is %d\n", errno, semid);
  
   cntr = shmp->impar;
   //shmp->write_complete = 0;
   if (pid == 0)
   printf("SHM_WRITE: CHILD: Now writing\n");
   else if (pid > 0)
   printf("SHM_WRITE: PARENT: Now writing\n");
   //printf("SHM_CNTR is %d\n", shmp->cntr);
   
   /* Increment the counter in shared memory by total_count in steps of 1 */
   for (numtimes = 0; numtimes < 1000; numtimes++) {
      cntr += 2;
      shmp->impar = cntr;
      printf("Number is %d\n", shmp->impar);
      /* Sleeping for a second for every thousand */
      shmp->buffer[numtimes]=cntr; 
      sleep_time = cntr % 11;
      if (sleep_time == 0)
      sleep(3);
   }
  // shmp->write_complete = 1;   
   if (pid == 0)
      printf("SHM_WRITE: CHILD: Writing Done\n");
      else if (pid > 0)
      printf("SHM_WRITE: PARENT: Writing Done\n");
      return;
}

