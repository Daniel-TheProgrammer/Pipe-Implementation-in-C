//Create Processes
//Report Processes
//Communnication between processes without just copying the memory over
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> //All the new functions are in this header
#include<sys/wait.h>
#include<errno.h>

int main(int argc,char* argv[]){
    //Pipe is an in memory file:a file that you can write and read from it
    //If we want to open a pipe we just write a function called pipe
    //Takes in an array of 2 integers which are the file descriptors of this PIpe
    //A File descriptor is like a key so we know where we have to read/write data to a file

    int fd[2]; //Define an array of 2Fd //Also we have 2fd because a pipe should have 2 ends & the 2 ends are store in here
    // fd[0] - read
    // fd[1] - write
    if (pipe(fd) == -1){
        printf("An error occured with opening the pipe\n");
        return 1;
    } //Pipe function is going to safe inside the array(the file descriptors that it opens) 

    // Above we have opened the pipe now we can fork
    //When you fork, the file descriptors in line 11 gets copied Over
    //Behind the scene those fd are assigned to the newly created clauses
    // SO they get inherited
    //if you close one fd at one process,orders work

    //So in this case fd[2] gets copied and inherited as well
    //Child process

    int id = fork(); //fork can't return -1 if it couldn't create a procees
    if(id == -1){
        printf("An error with fork\n");
        return 4;
    }
    if (id == 0)
    {
       close(fd[0]); //we have to close fd[0] because we don't read anything from that
       int x;
       printf("Input a Number:");
       scanf("%d", &x);
       // Here we need to check for errors by using if statement
       if (write(fd[1], &x, sizeof(int)) == -1){
           printf("An error occured with writing to the pipe\n");
           return 2; // 2 is different from the 1 above
       }  //Write permits you to write to any file
       //&x is where to get the memory to write from, i want to write in just an int
       close(fd[1]); //Close file descriptor
       // since its a pipe we usually close any one of the end on every process
       
       //Parent Process
    }else {
        close(fd[1]);
        int y;
        if(read(fd[0],&y,sizeof(int)) == -1){
            printf("An error occured with Reading the pipe\n");
            return 3;
        }
        y = y * 3;
        close(fd[0]);
        printf("Got from child process %d\n",y);
        //We have 4 close calls but we have 2 file descriptors
        // Since the 2 got inherited
        
    }
    
    return 0;
}