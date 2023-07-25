#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp;
c	har ch;
	fp = fopen(argv[1], "r");
	while ((ch = fgetc(fp)) != EOF) {
	printf("%c", ch);
	}
	fclose(fp);
	eturn 0;
}
