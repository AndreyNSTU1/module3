#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
int fd[2];
pid_t pid;
int n = atoi(argv[1]);
int i;
FILE *f;

if (argc != 2) {
fprintf(stderr, "Usage: %s n\n", argv[0]);
exit(1);
}

if (pipe(fd) == -1) {
perror("pipe");
exit(1);
}

pid = fork();

if (pid == -1) {
perror("fork");
exit(1);
} else if (pid == 0) {
/* child */
close(fd[0]);
srand(getpid());
for (i = 0; i < n; i++) {
int r = rand()%100;
write(fd[1], &r, sizeof(r));
}
close(fd[1]);
exit(0);
} else {
/* parent */
close(fd[1]);
f = fopen("output.txt", "w");
for (i = 0; i < n; i++) {
int r;
read(fd[0], &r, sizeof(r));
printf("%d\n", r);
fprintf(f, "%d\n", r);
}
fclose(f);
close(fd[0]);
wait(NULL);
}

return 0;
}
