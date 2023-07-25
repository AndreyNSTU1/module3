#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
int fd1[2], fd2[2];
pid_t pid;
int n = atoi(argv[1]);
int i;
FILE *f;

if (argc != 2) {
fprintf(stderr, "Usage: %s n\n", argv[0]);
exit(1);
}

if (pipe(fd1) == -1 || pipe(fd2) == -1) {
perror("pipe");
exit(1);
}

pid = fork();

if (pid == -1) {
perror("fork");
exit(1);
} else if (pid == 0) {
/* child */
close(fd1[0]);
close(fd2[1]);
srand(getpid());
for (i = 0; i < n; i++) {
int r = rand()%100+1;
write(fd1[1], &r, sizeof(r));
read(fd2[0], &r, sizeof(r));
printf("%d %d\n", r, r * 2);
fflush(stdout);
}
close(fd1[1]);
close(fd2[0]);
exit(0);
} else {
/* parent */
close(fd1[1]);
close(fd2[0]);
f = fopen("output.txt", "w");
for (i = 0; i < n; i++) {
int r;
read(fd1[0], &r, sizeof(r));
r *= 2;
write(fd2[1], &r, sizeof(r));
printf("%d %d\n", r / 2, r);
fprintf(f, "%d\n", r);
fflush(stdout);
}
fclose(f);
close(fd1[0]);
close(fd2[1]);
wait(NULL);
}

return 0;
}
