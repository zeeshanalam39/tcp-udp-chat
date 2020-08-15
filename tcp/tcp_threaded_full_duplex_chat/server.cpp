#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void *sendMsgThread(void *);
using namespace std;

int main()
{
  int fd = socket(AF_INET, SOCK_STREAM, 0);

  if (fd == -1)
  {
    perror("Socket Creation Failed: ");
    exit(-1);
  }

  struct sockaddr_in addr;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(83);

  if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
  {
    perror("Bind failed on socket :");
    exit(-1);
  }

  int backlog = 10;
  if (listen(fd, backlog) == -1)
  {
    perror("listening failed on socket:");
    exit(-1);
  }

  int connfd;
  struct sockaddr_in cliaddr;
  socklen_t cliaddr_len = sizeof(cliaddr);
  connfd = accept(fd, (struct sockaddr *)&cliaddr, &cliaddr_len);

  pthread_t thread; // Thread
  pthread_create(&thread, NULL, sendMsgThread, (void *)connfd);

  char buffer[100];
  while (1)
  {
    for (int i = 0; i < 100; i++)
    { // after
      buffer[i] = ' ';
    }
    recv(connfd, buffer, 100, 0);
    cout << "Message Received from Client : " << buffer << endl;
    cout << "Client IP: " << inet_ntoa(cliaddr.sin_addr) << " & Client Port: " << ntohs(cliaddr.sin_port) << endl;
    for (int i = 0; i < 100; i++)
    {
      buffer[i] = ' ';
    }
    memset(buffer, 0, sizeof(buffer));
  }
  close(fd);
  close(connfd);
  return 0;
}

void *sendMsgThread(void *sock)
{ // Thread function
  long connfd = (long)sock;
  char buffer[100];
  while (true)
  {
    for (int i = 0; i < 100; i++)
    { // after
      buffer[i] = ' ';
    }
    // send(connfd, buffer, strlen(buffer), 0);
    cout << "Enter message: " << endl;
    fgets(buffer, 100, stdin);
    send(connfd, buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    for (int i = 0; i < 100; i++)
    {
      buffer[i] = ' ';
    }
  }
}
