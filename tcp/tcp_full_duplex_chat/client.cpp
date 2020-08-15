#include<stdlib.h>
#include<iostream>
#include<errno.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

using namespace std;
int main()
{
int fd = socket(AF_INET, SOCK_STREAM, 0);

if(fd == -1)
{
perror("Socket Creation Failed: ");
exit(-1);
}

struct sockaddr_in s_addr;
s_addr.sin_family   = AF_INET;
s_addr.sin_port      = htons(80);
inet_aton("127.0.0.1", &s_addr.sin_addr);
connect(fd, (struct sockaddr*) &s_addr, sizeof(s_addr));

char buffer[100];
while(1) 
{
cout<<"Enter Message :";
fgets(buffer, 100, stdin);
send(fd, buffer, strlen(buffer),0);
for(int i=0; i<100; i++) {
  buffer[i]  =  ' ';
}

recv(fd, buffer, 100, 0);
cout<<"Message Received : "<<buffer<<endl;
}
close(fd);
return 0;

}
