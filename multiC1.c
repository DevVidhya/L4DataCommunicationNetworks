#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>

#include<string.h>
#include<pthread.h>

void* receive(void *network_fid)
{
int fid= *((int *)network_fid);
char message[100];
while(read(fid,message,sizeof(message))>0)
{
fputs(message,stdout);
memset(message,'\0',sizeof(memset));
}
}

int main(int argc, char* argv[])
{
if(argc<1)
printf("\n Less number of arguments ");

char username[100];
strcpy(username, argv[1]);

int network_fid=socket(AF_INET,SOCK_STREAM,0);
if(network_fid==0)
printf("\n Socket failure ");

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(7007);
server_address.sin_addr.s_addr=INADDR_ANY;

int connection_status = connect(network_fid, (struct sockaddr *) &server_address, sizeof(server_address));
if(connection_status<0)
printf("\n Error connecting ");

pthread_t recvthread;
pthread_create(&recvthread, NULL, &receive, &network_fid);

char msg[100];
while(fgets(msg,250,stdin)>0)
{
char msgtosend[200];
strcpy(msgtosend,username);
strcat(msgtosend," : ");
strcat(msgtosend,msg);
send(network_fid,msgtosend,strlen(msgtosend),0);
}

}
