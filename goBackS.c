#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>

#include<string.h>

int main()
{
int fid=socket(AF_INET,SOCK_STREAM,0);
if(fid==0)
printf("\n Error creating socket ");

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(8000);
server_address.sin_addr.s_addr=INADDR_ANY;

if(bind(fid,(struct sockaddr *)&server_address, sizeof(server_address))<0)
printf("\n Error binding ");

if(listen(fid,5)<0)
printf("\n Error listening ");

int client_fid=accept(fid,NULL,NULL);
if(client_fid<0)
printf(" Error accepting ");
 
int count,val;
while(1)
{
read(client_fid,&val,sizeof(val));
printf("\n Received Till : %d \n ", val);
memset(&val,'\0',sizeof(val));

printf("\n Ack Till : ");
scanf("%d",&count);
send(client_fid,&count,sizeof(count),0);
memset(&count,'\0',sizeof(count));
}

}




