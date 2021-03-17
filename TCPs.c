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
server_address.sin_port=htons(9002);
server_address.sin_addr.s_addr=INADDR_ANY;

if(bind(fid,(struct sockaddr *)&server_address, sizeof(server_address))<0)
printf("\n Error binding ");

if(listen(fid,5)<0)
printf("\n Error listening ");

int client_fid=accept(fid,NULL,NULL);
if(client_fid<0)
printf(" Error accepting ");
 
char msg[100];
read(client_fid,msg,sizeof(msg));

char temp;
int i,j;
for(i=0,j=strlen(msg)-1;i<j;i++,j--)
{
temp=msg[i];
msg[i]=msg[j];
msg[j]=temp;
}

send(client_fid,msg,strlen(msg),0);

printf("Reversed msg sent \n");
}




