#include <stdio.h>

int main(int argc) {
	char str[100];
	FILE *file;
	char *filename = "file.txt";
	if ((file = fopen(filename, "r")) == NULL) {
		printf("File '%s' does not exist. Do you want to create it? (y/n)\n", filename);
		char answer;
		scanf("%c", &answer);
		if (answer == 'y') {
			file = fopen(filename, "w");
			printf("File '%s' has been created.\n", filename);
			printf("Введите строку для записи в файл: ");
			char data[100];
			scanf("%s", data);
			fprintf(file, "%s\n", data);
			printf("Data has been written to file '%s'.\n", filename);
			return 1; 
		} else {
			printf("File '%s' has not been created.\n", filename);
			return 0;
		}
	} else {
		printf("File '%s' exists.\n", filename);
		printf("Введите строку для записи в файл: ");
		file = fopen(filename, "a"); 
		fgets(str, 100, stdin);
		fprintf(file, "%s\n", str);
		fclose(file);
		return 0; 
	}
	return 0;
}
