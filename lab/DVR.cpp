#include<iostream>
#include<stdio.h>
using namespace std;

struct node
{
int dist[100];
int from[100];
}rt[100];

int main()
{
int n,i,j;
cout<<"\n Enter number of nodes : ";
cin>>n;

cout<<"\n Enter matrix ";
for(i=0;i<n;i++)
for(j=0;j<n;j++)
{
cin>>rt[i].dist[j];
rt[i].from[j]=j;
}

for(i=0;i<n;i++)
for(j=0;j<n;j++)
for(int k=0;k<n;k++)
if(rt[i].dist[j]>rt[i].dist[k]+rt[k].dist[j])
{
rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
rt[i].from[j]=k;
cout<<"\n Updated from "<<i<<" to "<<j<<" through "<<k;
}

for(i=0;i<n;i++)
{
cout<<"\n\n Status of node "<<i;
for(j=0;j<n;j++)
cout<<"\n To "<<j<<" through "<<rt[i].from[j]<<" the distance is "<<rt[i].dist[j];
}

return 0;
}
