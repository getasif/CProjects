/**
 * Creates a process tree where The first parent has two children and one of 
 * that children has two additional children while the other has only one child
 * CS149 Project 1
 * Author: Akshay Hegde
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    printf("Immediately before the fork. This statement should print once.\n");
    int mpid = getpid();
    int pid;
    int i;
    int status;
    for (i = 0; i < 2; i++) {
        if ((pid = fork()) < 0) {
            printf("Sorry...cannot fork\n");
        }
        else if (pid == 0) {
            printf("I'm the child. My pid is %d and my parent is %d\n",
                    getpid(), getppid());
        }
        else {
            waitpid(pid, &status, 0);
            printf("I'm the parent. My pid is %d and my child is %d\n",
                    getpid(), pid);
        }
        if (i == 1) {
            if (getppid() == mpid) {
                pid = fork();
                if (pid == 0) {
                    printf("I'm the child. My pid is %d and my parent is %d\n",
                            getpid(), getppid());
                }
                else {
                    waitpid(pid, &status, 0);
                    printf("I'm the parent. My pid is %d and my child is %d\n",
                            getpid(), pid);
                }
            }
        }
    }
    exit(0);
}
