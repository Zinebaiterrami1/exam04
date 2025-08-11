#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// Declaration of your ft_popen function
int ft_popen(const char *file, char *const argv[], char type);

// int main(void) {
//     char *ls_args[] = {"ls", "-l", NULL};
//     int result;

//     // Test ft_popen in 'r' mode (read output of ls -l)
//     result = ft_popen("/bin/ls", ls_args, 'r');
//     if (result == -1) {
//         perror("ft_popen failed");
//         return 1;
//     }
//     printf("ft_popen returned: %d\n", result);
//     return 0;
// }

int main()
{
    int    fp = ft_popen("sort", (char *const []){"sort", NULL}, 'w');
    if (fp == -1) {
        perror("popen failed");
        return 1;
    }
    dprintf(fp, "banana\napple\ncherry\n");
    close(fp);
    // wait(NULL);
    return 0;
}
