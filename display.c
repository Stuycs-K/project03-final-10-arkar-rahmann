#include "display.h"
#include "data.h"
#include <time.h>
#include <signal.h>

#define VARNAME(Variable) (#Variable)

int compare(void *a, void *b) {
    struct finfo *finfo_a = *(struct finfo **)a;
    struct finfo *finfo_b = *(struct finfo **)b;
    return strcmp(finfo_a->entry->d_name, finfo_b->entry->d_name);
}

void display_dir(struct finfo **list, int size, int index, WINDOW *window) {
    qsort(list, size, sizeof(struct finfo *), compare);
    for(int i = 0; i < size; i++) {
        struct dirent *entry = list[i]->entry;

        if(i == index) wattron(window, A_STANDOUT);
        wprintw(window, "%s%c\n", entry->d_name, entry->d_type == DT_DIR ? '/' : ' ');
        wattroff(window, A_STANDOUT);
    } 
}

void display_metadata(struct stat *stat_buffer, WINDOW *window) {
    wprintw(window, "size: %ld bytes\n", stat_buffer->st_size);
    wprintw(window, "user id: %d\n", stat_buffer->st_uid);
    wprintw(window, "group id: %d\n", stat_buffer->st_gid);
    wprintw(window, "permissions: %d\n", stat_buffer->st_mode);
    wprintw(window, "last accessed: %s", ctime(&stat_buffer->st_atime));
    wprintw(window, "last modified: %s", ctime(&stat_buffer->st_mtime));
}

static void resize_handler(int sig) {
}
