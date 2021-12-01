
#include<stdio.h>
#include<unistd.h>

int main() {
    int pipefds[2];
    int returnstatus;
    int pid;
    char writemessages[2][20]={"Hi", "Hello"};
    char readmessage[20];
    returnstatus = pipe(pipefds);
    if (returnstatus == -1) {
    printf("Unable to create pipe\n");
    return 1;
 }