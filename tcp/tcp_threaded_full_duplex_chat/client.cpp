#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void *recvMsgThread(void *);
using namespace std;

int main()
{
  int fd = socket(AF_INET, SOCK_STREAM, 0); // Creation
  if (fd == -1)
  {
    perror("socket creation failed");
    exit(-1);
  }
  else
  {
    cout << "Creation - Success" << endl;
  }

  struct sockaddr_in s_addr; // Connection
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(83);
  inet_aton("127.0.0.1", &s_addr.sin_addr);
  connect(fd, (struct sockaddr *)&s_addr, sizeof(s_addr));

  pthread_t thread; // Thread
  pthread_create(&thread, NULL, recvMsgThread, (void *)fd);

  char buffer[100];
  while (1)
  {
    for (int i = 0; i < 100; i++)
    { // after
      buffer[i] = ' ';
    }
    cout << "Enter Message : " << endl;
    fgets(buffer, 100, stdin);
    send(fd, buffer, strlen(buffer), 0);
    for (int i = 0; i < 100; i++)
    {
      buffer[i] = ' ';
    }
    memset(buffer, 0, sizeof(buffer));
  }
  close(fd);
  return 0;
}

void *recvMsgThread(void *sock)
{ // Thread function
  long fd = (long)sock;
  char buffer[100];
  while (true)
  {
    if (recv(fd, buffer, 100, 0) > 0)
    {
      cout << "Message from server: " << buffer << endl;
      for (int i = 0; i < 100; i++)
      {
        buffer[i] = ' ';
      }
      memset(buffer, 0, sizeof(buffer));
    }
  }
}
