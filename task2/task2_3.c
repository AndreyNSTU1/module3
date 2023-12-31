#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(argv[1])) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			printf("%s\n", ent->d_name);
		}
		closedir(dir);
	} else {
		perror("");
		return 1;
	}
	return 0;
}
