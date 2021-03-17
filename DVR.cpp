#include <iostream>
using namespace std;


struct node
{
int dist[100];
int from[100];
}rt[100];

int main()
{
int n;
cout<<"\n Enter number of vertices : ";
cin>>n;

cout<<"\n Enter the graph";
for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
{
cin>>rt[i].dist[j];
rt[i].from[j]=j;
}

for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
for(int k=0;k<n;k++)
if(rt[i].dist[j]>rt[i].dist[k]+rt[k].dist[j])
{
rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
rt[i].from[j]=k;
}

for(int i=0;i<n;i++)
{
cout<<"\n State of "<<i;
for(int j=0;j<n;j++)
cout<<"\n Node "<<j<<" via node "<<rt[i].from[j]<<" has distance "<<rt[i].dist[j];
cout<<"\n\n";
}

}
