    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/wait.h>

    #define MAX_ARGS 10

    int main() {
    char input[1024];
    char *args[MAX_ARGS];
    int i;

    while (1) {
    printf("> ");
    fgets(input, 1024, stdin);

    // Remove trailing newline
    input[strlen(input) - 1] = '\0';

    // Split input into arguments
    args[0] = strtok(input, " ");
    for (i = 1; i < MAX_ARGS; i++) {
    args[i] = strtok(NULL, " ");
    if (args[i] == NULL) {
    break;
    }
    }

    // Exit if no command entered
    if (args[0] == NULL) {
    continue;
    }

    // Exit if "exit" command entered
    if (strcmp(args[0], "exit") == 0) {
    break;
    }

    // Create pipe for output redirection
    int pipefd[2];
    pipe(pipefd);

    // Fork process
    pid_t pid = fork();

    if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
    } else if (pid == 0) {
    // Child process

    // Redirect output to pipe
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    // Execute command
    execvp(args[0], args);

    // If execvp returns, there was an error
    perror(args[0]);
    exit(EXIT_FAILURE);
    } else {
    // Parent process

    // Wait for child process to finish
    wait(NULL);

    // Read output from pipe and print it
    close(pipefd[1]);
    char buf;
    while (read(pipefd[0], &buf, 1) > 0) {
    putchar(buf);
    }
    close(pipefd[0]);
    }
    }

    return 0;
    }


