#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
int fd;
int i;
int r;

/* create the FIFO (named pipe) */
mkfifo(FIFO_NAME, 0666);

/* open the FIFO */
fd = open(FIFO_NAME, O_WRONLY);

srand(getpid());
for (i = 0; i < 10; i++) {
r = rand()%100+1;
write(fd, &r, sizeof(r));
}

/* close the FIFO */
close(fd);

/* remove the FIFO */
unlink(FIFO_NAME);

return 0;
}
