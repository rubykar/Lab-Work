#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

int main() {
    int sockfd;
    int arr[MAXLINE]; // Array to store sent integers
    int sortedArr[MAXLINE]; // Array to store received sorted integers
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Input integers into the array (for demonstration purposes, you can input your own integers)
    int numIntegers;
    std::cout << "Enter the number of integers: ";
    std::cin >> numIntegers;
    std::cout << "Enter " << numIntegers << " integers: ";
    for (int i = 0; i < numIntegers; ++i) {
        std::cin >> arr[i];
    }

    // Sending the array to the server
    sendto(sockfd, arr, numIntegers * sizeof(int), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    std::cout << "Array sent to the server." << std::endl;

    socklen_t len = sizeof(servaddr);
    int n = recvfrom(sockfd, sortedArr, MAXLINE * sizeof(int), MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
    int numSortedIntegers = n / sizeof(int);

    // Displaying the sorted array received from the server
    std::cout << "Sorted array received from the server: ";
    for (int i = 0; i < numSortedIntegers; ++i) {
        std::cout << sortedArr[i] << " ";
    }
    std::cout << std::endl;

    close(sockfd);
    return 0;
}
