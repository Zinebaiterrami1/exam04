#include <stdio.h>
#include <string.h>

int picoshell(char **cmds[]);

int main(int argc, char *argv[])
{
    // Hardcode a small array of commands for testing
    char *cmd1[] = {"/bin/ls", NULL};
    char *cmd2[] = {"/usr/bin/grep", "picoshell", NULL};
    char **cmds1[] = {cmd1, cmd2, NULL};

    char *cmd3[] = {"echo", "squalala", NULL};
    char *cmd4[] = {"cat", NULL};
    char *cmd5[] = {"sed", "s/a/b/g", NULL};
    char **cmds2[] = {cmd3, cmd4, cmd5, NULL};

    printf("=== Test 1 ===\n");
    picoshell(cmds1);

    printf("\n=== Test 2 ===\n");
    picoshell(cmds2);

    return 0;
}
