#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int parentToChild[2];

    if (pipe(parentToChild) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(parentToChild[1]);

        char messagefromParent[100];
        read(parentToChild[0], messagefromParent, sizeof(messagefromParent));
        printf("Child received from parent: %s\n", messagefromParent);

        close(parentToChild[0]);

        exit(EXIT_SUCCESS);
    } else {
        close(parentToChild[0]);

        char *messageToChild = argv[1];

        write(parentToChild[1], messageToChild, strlen(messageToChild) + 1);

        close(parentToChild[1]);

        wait(NULL);

        exit(EXIT_SUCCESS);
    }

    return 0;
}
