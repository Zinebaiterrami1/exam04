#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

// int picoshell(char **cmd[])
// {
//     int i;
//     int pid;
//     int fd[2];
//     int prev;
//     int status;
//     int exit_status;

//     if(!cmd)
//         return (1);
//     i = 0;
//     prev = -1;
//     exit_status = 0;
//     while(cmd[i])
//     {
//         if(cmd[i + 1] && pipe(fd))
//         {
//             if(prev != -1)
//                 close(prev);
//             return (1);
//         }
//         pid = fork();
//         if(pid < 0)
//         {
//             if(prev != -1)
//                 close (prev);
//             if(cmd[i + 1])
//             {
//                 close(fd[0]);
//                 close(fd[1]);
//             }
//         }
//         if(pid == 0)
//         {
//             if(prev != -1)
//             {
//                 dup2(prev, 0);
//                 close(prev);
//             }
//             if(cmd[i + 1])
//             {
//                 dup2(fd[1], 1);
//                 close(fd[1]);
//                 close(fd[0]);
//             }
//             execvp(cmd[i][0], cmd[i]);
//             exit(1);
//         }
//         if(prev != -1)
//             close(prev);
//         if(cmd[i + 1])
//         {
//             prev = fd[0];
//             close(fd[1]);
//         }
//         i++;
//     }
//     if(prev != -1)
//         close(prev);
//     while(wait(&status) != -1)
//     {
//         if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
//             exit_status = 1;
//     }
//     return (exit_status);
// }

// int main(){
//     char *cmd1[] = {"/bin/ls", NULL};
//     char *cmd2[] = {"/usr/bin/grep", "picoshell", NULL};
//     char **cmd[] = {cmd1, cmd2, NULL};

//     picoshell(cmd);
// }

// int picoshell(char **cmd[])
// {
//     int i;
//     int pid;
//     int fd[2];
//     int status;
//     int exit_status;
//     int prev;

//     if(!cmd)
//         return (1);
//     i = 0;
//     prev = -1;
//     exit_status = 0;
//     while(cmd[i])
//     {
//         if(cmd[i + 1] && pipe(fd))
//         {
//             if(prev != -1)
//                 close (prev);
//             return (1);
//         }
//         pid = fork();
//         if(pid < 0)
//         {
//             if(prev != -1)
//                 close (prev);
//             if(cmd[i + 1])
//             {
//                 close(fd[0]);
//                 close(fd[1]);
//             }
//             return (1);
//         }
//         if(pid == 0)
//         {
//             if(prev != -1)
//             {
//                 dup2(prev, 0);
//                 close (prev);
//             }
//             if(cmd[i + 1])
//             {
//                 dup2(fd[1], 1);
//                 close(fd[1]);
//                 close(fd[0]);
//             }
//             execvp(cmd[i][0], cmd[i]);
//             exit(1);
//         }
//         if(prev != -1)
//             close(prev);
//         if(cmd[i + 1])
//         {
//             prev = fd[0];
//             close(fd[1]);
//         }
//         i++;
//     }
//     if(prev != -1)
//         close (prev);
//     while(wait(&status) != -1)
//     {
//         if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
//             exit_status = 1;
//     }
//     return (exit_status);
// }

int picoshell(char **cmd[])
{
    int i;
    int fd[2];
    int exit_status;
    int prev;
    int pid;
    int status;

    if(!cmd)
        return (1);
    i = 0;
    exit_status = 0;
    prev = -1;
    while(cmd[i])
    {
        if(cmd[i + 1] && pipe(fd))
        {
            if(prev != -1)
                close(prev);
            return (1);
        }
        pid = fork();
        if(pid < 0)
        {
            if(prev != -1)
                close(prev);
            if(cmd[i + 1])
            {
                close (fd[1]);
                close(fd[0]);
            }
            return (1);
        }
        if(pid == 0)
        {
            if(prev != -1)
            {
                dup2(prev, 0);
                close(prev);
            }
            if(cmd[i + 1])
            {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
            }
            execvp(cmd[i][0], cmd[i]);
            exit(1);
        }
        if(prev != -1)
            close(prev);
        if(cmd[i + 1])
        {
            prev = fd[0];
            close(fd[1]);
        }
        i++;
    }
    if(prev != -1)
        close(prev);
    while(wait(&status) != -1)
    {
        if(WEXITED(status) && WEXITSTATUS(status) != 0)
            exit_status = 1;
    }
    return (exit_status);
}