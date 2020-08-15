
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

using namespace std;
int main()
{

int fd=socket(AF_INET,SOCK_STREAM,0);         // Socket Creation
if (fd==-1)
{
perror("Socket Creation Failed");
exit(-1);
}
else
{
cout<<"Creation - Success"<<endl;
}

struct sockaddr_in addr;			//Binding 
addr.sin_addr.s_addr    =INADDR_ANY;
addr.sin_family 	= AF_INET;
addr.sin_port           =htons(81);


if(bind(fd,(struct sockaddr *)&addr,sizeof(addr))==-1)
{
perror("Binding failed on socket: ");
}
else
{
cout<<"Binding - Success"<<endl;
}

int backlog=10;					//Listen
if (listen(fd,backlog)==-1)
{
perror("Listening failed on socket: ");
exit(-1);
}
else
{
cout<<"Listen - Success"<<endl;
}

int connfd;					//Accept
struct sockaddr_in cliaddr;
socklen_t cliaddr_len=sizeof(cliaddr);
connfd=accept(fd,(struct sockaddr*)&cliaddr,&cliaddr_len);

char buffer[100];				//Message
while(1)
{
recv(connfd,buffer,100,0);
cout<<"Message Received: "<<buffer<<endl;
}
close(fd);
close(connfd);
return 0;

}
