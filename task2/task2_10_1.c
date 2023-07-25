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

/* open the FIFO */
fd = open(FIFO_NAME, O_RDONLY);

for (i = 0; i < 10; i++) {
read(fd, &r, sizeof(r));
printf("%d\n", r);
fflush(stdout);
}

/* close the FIFO */
close(fd);

return 0;
}
