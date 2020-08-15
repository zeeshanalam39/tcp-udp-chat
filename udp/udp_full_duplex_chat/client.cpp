#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 500
#define PORT 2031
#define SA struct sockaddr

int main()
{
	char buff[MAX];
	int sockfd, n;
	int len2;
	char ipAndPort[35] = "127.0.0.1\n2027\n";

	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	bzero(&servaddr, sizeof(len2));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	socklen_t len = sizeof(servaddr);
	len2 = sizeof(servaddr);

	for (;;)
	{
		printf("\nEnter string : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		for (int i = 0; i < sizeof(ipAndPort); i++)
			buff[n++] = ipAndPort[i];
		sendto(sockfd, buff, sizeof(buff), 0, (SA *)&servaddr, len2);

		bzero(buff, sizeof(buff));
		recvfrom(sockfd, buff, sizeof(buff), 0, (SA *)&servaddr, &len);
		printf("From Server : %s\n", buff);
		if (strncmp("exit", buff, 4) == 0)
		{
			printf("Client Exit...\n");
			break;
		}
	}
	//close(sockfd);
}
