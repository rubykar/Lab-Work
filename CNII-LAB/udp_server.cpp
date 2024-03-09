#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <algorithm>

#define PORT     8080
#define MAXLINE 1024

int main() {
    int sockfd;
    int arr[MAXLINE]; // Array to store received integers
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int n = recvfrom(sockfd, arr, MAXLINE * sizeof(int), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    int numIntegers = n / sizeof(int);

    // Sorting the received array
    std::sort(arr, arr + numIntegers);

    // Sending the sorted array back to the client
    sendto(sockfd, arr, numIntegers * sizeof(int), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);

    std::cout << "Sorted array sent to the client." << std::endl;

    close(sockfd);
    return 0;
}
