#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#define MAXSIZE     128

//msgbuf2 sbuf;

void die(char *s)
{
  perror(s);
  exit(1);
}
struct msgbuf2
{
    long    mtype;
    char    mtext[MAXSIZE];
};

void threads(int n ) 
{
    std::this_thread::sleep_for (std::chrono::seconds(n));
  //std::cout << "pause " << n << " seconds ended messaging : msg" << msg <<"\n";
    //int n_th = n;

    char msg_th[MAXSIZE] ;
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    msgbuf2 sbuf;
    size_t buflen;

    key = 1234;

    if ((msqid = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
      die("msgget");

    //Message Type
    sbuf.mtype = 1;

    printf("Enter a message to add to message queue : ");
    scanf("%[^\n]",sbuf.mtext);
    getchar();

    buflen = strlen(sbuf.mtext) + 1 ;

    if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
    {
        printf ("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
        die("msgsnd");
    }
    else
        printf("Message Sent\n");
    exit(0);
}




main()
{
    //msgbuf sbuf;
    std::cout << "Spawning and detaching 3 threads...\n";
    std::thread (threads,10).detach();std::cout <<"\n"<<"\n";
    std::thread (threads,10).detach();std::cout <<"\n"<<"\n";
    std::thread (threads,10).detach();std::cout <<"\n"<<"\n";
    std::cout << "Done spawning threads.\n";

    threads(20);

    //exit(0);
}