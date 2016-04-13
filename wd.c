#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {
    char path[256];

    if (argc < 3) {
        fprintf(stderr, "usage: %s WORKING_DIR PROGRAM [ARGS...]\n", argv[0]);
        return -1;
    }

    if (!getcwd(path, sizeof (path) - strlen(argv[2]) - 2)) {
        perror("getcwd");
        return -1;
    }

    strcat(path, "/");
    strcat(path, argv[2]);

    if (access(path, F_OK) < 0) {
        perror(path);
        return -1;
    }

    chdir(argv[1]);
    execve(path, argv + 2, envp);
    return -1;
}
