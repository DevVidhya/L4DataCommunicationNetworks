#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>

#include<string.h>

int main()
{
int network_fid=socket(AF_INET,SOCK_DGRAM,0);
if(network_fid==0)
printf("\n Error creating socket ");

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(8080);
server_address.sin_addr.s_addr=INADDR_ANY;

char msg[100];
int length=sizeof(server_address);
printf("\n Enter a string : ");
scanf("%s", msg);

sendto(network_fid, msg, strlen(msg), 0, (struct sockaddr *) &server_address, sizeof(server_address));
memset(msg,'\0',sizeof(msg));
recvfrom(network_fid, msg, sizeof(msg), 0, (struct sockaddr *) &server_address, &length);

printf("\n Reversed string : %s \n", msg);

return 0;
}


