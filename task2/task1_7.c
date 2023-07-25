#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	char str[100];
	fp = fopen(argv[1], "a");
	printf("Введите строку для записи в файл: ");
	fgets(str, 100, stdin);
	fprintf(fp, "%s\n", str);
	fclose(fp);
	return 0;
}
