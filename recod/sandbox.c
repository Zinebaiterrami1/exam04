#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void f(void)
{
    printf("hello");
}

// int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
// {
//     int pid;
//     int status;
//     int code;

//     pid = fork();
//     if(pid == -1)
//         return (-1);
//     if(pid == 0)
//     {
//         alarm(timeout);
//         f();
//         exit(0);
//     }
//     if(waitpid(pid, &status, 0) == -1)
//         return (-1);
//     if(WIFEXITED(status))
//     {
//         code = WEXITSTATUS(status);
//         if(code == 0)
//         {
//             if(verbose)
//                 printf("Nice function!\n");
//             return (1);
//         }
//         else
//         {
//             if(verbose)
//                 printf("Bad function: exited with code %d\n", code);
//             return (0);
//         }
//     }
//     if(WIFSIGNALED(status))
//     {
//         int sig = WTERMSIG(status);
//         if(sig == SIGALRM)
//         {
//             if(verbose)
//                 printf("Bad function: timed out after %d seconds\n", timeout);
//             return (0);
//         }
//         else
//         {
//             if(verbose)
//                 printf("Bad function: %s\n", strsignal(sig));
//             return (0);
//         }
//     }
//     return (-1);
// }

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    int pid;
    int status;
    
    pid = fork();
    if(pid == -1)
        return (-1);
    if(pid == 0)
    {
        alarm(timeout);
        f();
        exit(0);
    }
    if(waitpid(pid, &status, 0) == -1)
        return (-1);
    if(WIFEXITED(status))
    {
        int code = WEXITSTATUS(status);
        if(code == 0)
        {
            if(verbose)
                printf("Nice function\n");
            return (1);
        }
        else
        {
            if(verbose)
                printf("Bad function: exited with code %d\n", code);
            return (0);
        }
    }
    if(WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);
        if(sig == SIGALRM)
        {
            if(verbose)
                printf("Bad function:  timed out after %d seconds\n", timeout);
            return (0);
        }
        else
        {
            if(verbose)
                printf("Bad function: %s\n", strsignal(sig));
            return (0);
        }
        return (-1);
    }
}
int main()
{
    sandbox(f, 9, true);
    return (0);
}