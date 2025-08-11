#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void f(void)
{
    raise(_BITS_SIGNUM_ARCH_H);
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    int pid;
    int status;
    int exit_status;
    int sig;

    pid = fork();
    if(pid < 0)
        return(-1);
    if(pid == 0)
    {
        alarm(timeout);
        f();
        exit(0);
    }
    if(waitpid(pid, &status, 0) == -1)
        return(-1);
    if(WIFSIGNALED(status))
    {
        sig = WTERMSIG(status);
        if(sig == SIGALRM)//SIGALRM
        {
            if(verbose)
                printf("timeout at %d second\n", timeout);
            return(0);
        }
        else
        {
            if(verbose)
                printf("end with signal %s \n", strsignal(sig));
            return(0);
        }
    }
    if(WIFEXITED(status))
    {
        exit_status = WEXITSTATUS(status);
        if(exit_status == 0)
        {
            if(verbose)
                printf("nice funct\n");
            return(1);
        }
        else
        {
            if(verbose)
                printf("bad funct exit with code %d\n", exit_status);
            return(0);
        }
    }
    return(-1);
}