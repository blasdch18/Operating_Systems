#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <signal.h>
#include <pthread.h>


void randomizer()
{
	sleep(1);
	long randnum =0;
	char randNumbers[100];
	randnum= rand()%1000;
	sprintf (randNumbers, "%ld", randnum);
	printf("Number generated: %s\n", randNumbers);
	
}

void *signalizer(int signal_num)
{
	pthread_t thread_id;
	if(signal_num == 2)
	{
		long randnum =0;
		printf("heyy!!\n" );
		randomizer();
		pthread_create (&thread_id, NULL, randomizer, NULL); 
		pthread_join(thread_id, NULL);
		printf("thread joined!! \n" );
	}
}

int main()
{
	
	signal(SIGINT , signalizer);
	while(1)
	{
		printf(" my PID is : %d\n",getpid());
		sleep(1);
	}
	return 0;
}


def giraCaballo(n,ruta,u,limite):
        u.asignarColor('gris')
        ruta.append(u)
        if n < limite:
            listaVecinos = list(u.obtenerConexiones())
            i = 0
            hecho = False
            while i < len(listaVecinos) and not hecho:
                if listaVecinos[i].obtenerColor() == 'blanco':
                    hecho = giraCaballo(n+1, ruta, listaVecinos[i], limite)
                i = i + 1
            if not hecho:  # prepararse para retroceder
                ruta.pop()
                u.asignarColor('blanco')
        else:
            hecho = True
        return hecho