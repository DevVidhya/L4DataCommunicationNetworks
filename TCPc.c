#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>

#include<string.h>

int main()
{
int network_fid=socket(AF_INET,SOCK_STREAM,0);
if(network_fid==0)
printf("Socket failure \n");

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(9002);
server_address.sin_addr.s_addr=INADDR_ANY;

int connection_status=connect(network_fid,(struct sockaddr *) &server_address,sizeof(server_address));
if(connection_status==-1)
printf("Error connecting to remote socket \n");

char msg[100];
printf("Enter a string : ");
scanf("%s", msg);

send(network_fid,msg,strlen(msg),0);
read(network_fid,msg,sizeof(msg));

printf("\nReversed string is %s\n",msg);

}

