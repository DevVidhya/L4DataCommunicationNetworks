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

int msg=5,ack;
while(1)
{
printf("\n Sent till : %d \n", msg);
send(network_fid,&msg,sizeof(msg),0);
if(msg==15)
break;

read(network_fid,&ack,sizeof(ack));
printf("\n Acknowledged till : %d", ack);

msg=ack+5;
if(msg>15)
msg=15;
}

return 0;
}

