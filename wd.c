#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

int main(int argc, char **argv, char **envp) {
    char path[PATH_MAX];

    if (argc < 3) {
        fprintf(stderr, "usage: %s WORKING_DIR PROGRAM [ARGS...]\n", argv[0]);
        return -1;
    }

    if (argv[2][0] == '/') {
        strncpy(path, argv[2], sizeof (path) - 1);
    } else {
        if (!getcwd(path, sizeof (path) - strlen(argv[2]) - 2)) {
            perror("getcwd");
            return -1;
        }

        strcat(path, "/");
        strcat(path, argv[2]);
    }

    if (access(path, F_OK) < 0) {
        perror(path);
        return -1;
    }

    chdir(argv[1]);

    int status = execve(path, argv + 2, envp);

    if (status < 0)
        perror("execve");

    return status;
}
