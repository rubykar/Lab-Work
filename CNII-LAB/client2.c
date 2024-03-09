// Client side C program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char hello[1000];
	char* noconnection = "no";
	char buffer[1024] = { 0 };
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((status
		= connect(client_fd, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	int p = 1;
	while( p == 1){
	printf("Enter 1 if you want to continue sending info to the server : ");
	scanf("%d",&p);
	if( p == 1){
	printf("Enter the info you wnat to send to the server : ");
	scanf("%s",hello);
	send(client_fd, hello, strlen(hello), 0);
	printf("Hello message sent\n");
	if(strcmp(hello, noconnection) == 0){
    send(client_fd, noconnection, strlen(noconnection), 0);
    close(client_fd);
    break;
	}
	valread = read(client_fd, buffer,
				1024 - 1); // subtract 1 for the null
							// terminator at the end
	printf("%s\n", buffer);
	}
	else{
		send(client_fd, noconnection, strlen(noconnection), 0);
		close(client_fd);
		break;
	}
	
	}
	// closing the connected socket

	return 0;
}
