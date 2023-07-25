#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ncurses.h>

int main(int argc, char *argv[]) {
DIR *dir;
struct dirent *ent;
struct stat st;
if ((dir = opendir(argv[1])) != NULL) {
initscr();
noecho();
cbreak();
keypad(stdscr, TRUE);
int row = 0;
while ((ent = readdir(dir)) != NULL) {
char *filename = ent->d_name;
char *type = "";
if (stat(filename, &st) == 0) {
if (S_ISREG(st.st_mode)) {
type = "regular file";
} else if (S_ISDIR(st.st_mode)) {
type = "directory";
} else if (S_ISCHR(st.st_mode)) {
type = "character device";
} else if (S_ISBLK(st.st_mode)) {
type = "block device";
} else if (S_ISFIFO(st.st_mode)) {
type = "FIFO/pipe";
} else if (S_ISLNK(st.st_mode)) {
type = "symlink";
} else if (S_ISSOCK(st.st_mode)) {
type = "socket";
}
}
mvprintw(row++, 0, "%s (%s)", filename, type);
}
closedir(dir);
refresh();
getch();
endwin();
} else {
perror("");
return 1;
}
return 0;
}
