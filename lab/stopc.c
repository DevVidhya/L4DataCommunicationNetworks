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
printf("\n Socket failure ");

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(9999);
server_address.sin_addr.s_addr=INADDR_ANY;

if(connect(network_fid,(struct sockaddr *)&server_address, sizeof(server_address))<0)
printf("\n Connection failure ");

int msg;
while(1)
{
printf("\n Enter the packet number to send : ");
scanf("%d", &msg);
send(network_fid,&msg,sizeof(msg),0);

memset(&msg,'\0',sizeof(msg));
read(network_fid,&msg,sizeof(msg));

printf("\n Expected : %d ", msg);
}

return 0;
}

