#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	char ch;
	fp = fopen(argv[1], "r");
	while ((ch = getc(fp)) != EOF) {
	printf("%c", ch);
	}
	fclose(fp);
	return 0;
}
