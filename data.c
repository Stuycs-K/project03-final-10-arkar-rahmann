#include "data.h"

bool create_file(char *name) {
    int fd = open(name, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) return false;
    close(fd);
    return true;
}

struct finfo **get_file_listing(char *dir, int *size) {
    DIR *d = opendir(dir);
    struct dirent *entry;

    *size = 0;
    while ((entry = readdir(d))) ++(*size);

    closedir(d);
    d = opendir(dir);
    struct finfo **list = malloc(*size * sizeof(struct finfo *));
    struct finfo **itr = list;

    while ((entry = readdir(d))) {
        struct finfo *f = malloc(sizeof(struct finfo));

        f->entry = entry;
        if (entry->d_type == DT_DIR) f->stat_buffer = NULL;
        else {
            f->stat_buffer = malloc(sizeof(struct stat));
            stat(entry->d_name, f->stat_buffer);
        }

        *itr = f;
        ++itr;
    }
    closedir(d);

    return list;
}

bool rename_file(char *old_name, char *new_name) {
    if (rename(old_name, new_name) == 0) {
        return true;
    }
    else {
        perror("Error renaming file");
        return false;
    }
}

bool delete_file(char *name) {
    if (remove(name) == 0) {
        return true;
    }
    else {
        perror("Error deleting file");
        return false;
    }
}

bool move_file(char *old, char *new) {
    return rename_file(old, new);
}
