#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int ft_popen(const char *file, char *const argv[], char type)
// {
//     if(!file || !argv || (type != 'w' && type != 'r'))
//         return (-1);
//     int pid;
//     int fd[2];
//     if(pipe(fd))
//         return (-1);
//     pid = fork();
//     if(pid == 0)
//     {
//         if(type == 'r')
//         {
//             close(fd[0]);
//             dup2(fd[1], STDOUT_FILENO);
//             close(fd[1]);
//         }
//         else
//         {
//             close(fd[1]);
//             dup2(fd[0], STDIN_FILENO);
//             close(fd[0]);
//         }
//         execvp(file, argv);
//         exit (1);
//     }
//     if(type == 'r')
//     {
//         close(fd[1]);
//         return (fd[0]);
//     }
//     else
//     {
//         close(fd[0]);
//         return (fd[1]);
//     }
// }

int ft_popen(char *file, char *const argv[], char type)
{
    if(!file || !argv || (type != 'w' && type != 'r'))
        return (-1);
    int pid;
    int fd[2];
    if(pipe(fd) < 0)
        return (-1);
    pid = fork();
    if(pid == -1)
        return (-1);
    if(pid == 0)
    {
        if(type == 'r')
        {
            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);
        }
        else
        {
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
        }
        execvp(file, argv);
        exit (1);
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

int main()
{
    int fd = ft_popen("sort", (char *const []){"sort", NULL}, 'w');
    dprintf(fd, "banan\nzineb\napple\n");
    return (0);
}

