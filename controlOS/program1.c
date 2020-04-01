#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

	const char *name = "lab";
	const int SIZE = 4096;

	int shm_fd;
	void *ptr;
	int i;
 
#define TAM 1024
 
 
int main()
{
    int pid,memoriaID;
    char *punteroAMemoriaCompartida = NULL;
    puts("Vamos a usar memoria compartida con varios procesos");
    
    if((memoriaID = shmget(1315511,TAM,0664|IPC_CREAT))==-1) { //El primer valor es un identificador unico, puede dar problemas
        fprintf(stderr,"Error al reservar la memoria");
    } //Creo la memoria compartida
    pid = fork();
    switch(pid) {
        case -1:
            fprintf(stderr,"Error al hacer el fork");
        break;
        case 0: //El hijo
            punteroAMemoriaCompartida = shmat(memoriaID,(void *)0,0); //Asociacion
            puts("Soy el hijo");
            strcpy(punteroAMemoriaCompartida,"Somos Binarios");
        break;
        default:
            sleep(5); //Se explicara mas adelante
            punteroAMemoriaCompartida = shmat(memoriaID,NULL,0); //Asociacion
            puts("Soy el padre");
            printf("Texto en memoria compartida: %s\n",punteroAMemoriaCompartida);
            
            shmdt(&punteroAMemoriaCompartida); //Desasociacion
            if(shmctl(memoriaID,IPC_RMID,NULL)==-1){
                fprintf(stderr,"Error al liberar la memoria");
            }
        break;          
    }   
    return 0;
	/* open the shared memory segment */
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	/* now read from the shared memory region */
	printf("%s",ptr);

	/* remove the shared memory segment */
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}




	return 0;
}
