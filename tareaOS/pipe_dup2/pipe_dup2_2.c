#include  <fcntl.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <sys/types.h>
#include  <sys/wait.h>
#include  <sys/stat.h>
#include  <termios.h>
#include  <unistd.h>

// run as :  pipe_dump2.exe CMD  OUTPUT_FILE
int main(int argc, char* argv[])
{


pid_t pid;
int ofd;
char *cmd,  *input;

cmd = argv[1];
input = argv[2];
pid = fork();
if(pid==0) // Child
   {
    printf("Running %s < %s\n",cmd,input);
    ofd=open(input,0644);
    //write(ofd, string, (strlen(string)+1));
    dup2(ofd,0); // same as: close(1); dup(odf);
    execlp(cmd, cmd, (char*) NULL);
    }
wait((int *)NULL);
}
