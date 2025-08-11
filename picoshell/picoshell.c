#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int    picoshell(char **cmds[])
{
    int pid;
    int fd[2];
    int i = 0;
    int prev = -1;
    int status;
    int exit_status = 0;

    while(cmds[i])
    {
        if(cmds[i + 1]) //not last
        {
            if (pipe(fd) == -1)
            {
                if (prev != -1)
                    close(prev);
                return 1;
            }
        }
        pid = fork();
        if(pid < 0)
        {
            if (prev != -1)
                close(prev);
            if (cmds[i + 1]) {
                close(fd[0]);
                close(fd[1]);
            }
            return 1;
        }
        if(pid == 0)
        {
            if(prev != -1) //not first
            {
                dup2(prev, 0);
                close(prev);
            }
            if(cmds[i + 1])//not last
            {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        if(prev != -1)
            close(prev);
        if(cmds[i + 1]) //not last (save old pipe read end)
        {
            prev = fd[0];
            close(fd[1]);
        }
        i++;
    }
    if(prev != -1)
        close (prev);
    while(wait(&status) != -1)
    {
        if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
            exit_status = 1;
    }
    return (exit_status);
}