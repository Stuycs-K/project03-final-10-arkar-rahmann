#include "process.h"

void open_file_program(char *name) {
    pid_t pid = fork();

    if (pid == 0) execlp("xdg-open", "xdg-open", name, NULL);
    else {
        int status;
        wait(&status);
    }
}

struct finfo **cd(char *dir, int *size) {
    char path[] = "./";
    strcat(path, dir);
    chdir(path);
    struct finfo **list = get_file_listing(".", size);
    return list;
}

void err(char *src) {
    if(errno != 0) {
        fprintf(stderr, "%s errno %d: %s\n", src, errno, strerror(errno));
        exit(1);
    }
}

