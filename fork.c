/**
 *  Testing fork -- each process reports its PID or it's parent/child's PID
 *  CS149 Project 1
 *  Author: Akshay Hegde
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("Immediately before the fork. Only one process at this point.\n");
    int pid = fork();
    printf("Immediately after the fork. This statement should print twice.\n");

    if (pid != 0) {
        printf("I'm the parent. My pid is %d. My child's pid is %d\n", getpid(),
                pid);
    }
    else {
        printf("I'm the child. My pid is %d. My parent's pid is %d\n", getpid(),
                getppid());
    }

    return 0;
}
