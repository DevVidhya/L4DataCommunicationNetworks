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
printf("\n Error creating socket ");

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(9090);
server_address.sin_addr.s_addr=INADDR_ANY;

int connection_status=connect(network_fid, (struct sockaddr *)&server_address,sizeof(server_address));
if(connection_status<0)
printf("\n Error connecting ");
int msg=5,count;

while(1)
{
if(msg>15)
msg=15;
printf("\n Sent Till : %d ", msg);

send(network_fid,&msg,sizeof(msg),0);
read(network_fid,&count,sizeof(count));


printf("\n Acknowledged Till : %d \n", count);
if(count==15)
break;
msg=count+5;
}

return 0;
}
