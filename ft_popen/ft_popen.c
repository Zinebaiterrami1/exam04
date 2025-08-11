#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int ft_popen(const char *file, char *const argv[], char type)
{
    int pid;
    int fd[2];
    int i;

    i = 0;
    if(!file || !argv || (type != 'w' && type != 'r'))
        return (-1);
    if(pipe(fd) < 0)
        return (-1);
    pid = fork();
    if(pid < 0)
        return -1;
    if(pid == 0)
    {
        if(type == 'w')
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        else if(type == 'r')
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        }
        execvp(file, argv);
        exit(1);
    }
    if(type == 'r')
    {
        close(fd[1]);
        return (fd[0]);
    }
    else
    {
        close(fd[0]);
        return (fd[1]);
    }
}
