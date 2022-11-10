#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stdlib.h>
#include<iostream>
#include<cstring>
#define maxn 10007
using namespace std;
int n,m,ans=1;
int sc[107][107],in[maxn],head[maxn],t,f[maxn],vis[maxn];
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

struct node{
    int to,next;
}edge[maxn<<2];

void add(int u,int v){
    edge[++t]=(node){v,head[u]},head[u]=t;
    in[v]++;
}

queue<int>q;

int SPFA(int ori){
    int re=0;
    memset(f,0,sizeof(f));
    f[ori]++;q.push(ori);
    while(!q.empty()){
        int x=q.front();q.pop();vis[x]=0;
        for(int i=head[x];i;i=edge[i].next){
            int y=edge[i].to;
            if(f[y]<f[x]+1){
                f[y]=f[x]+1;re=max(re,f[y]);
                if(!vis[y]){
                    q.push(y),vis[y]=1;
                }
            }
        }
    }
    return re;
}

int main(){
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&sc[i][j]);
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<4;k++){
                int x=i+dir[k][0],y=j+dir[k][1];
                if(sc[x][y]>sc[i][j]) add((i-1)*m+j,(x-1)*m+y);
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!in[(i-1)*m+j]){
                ans=max(ans,SPFA((i-1)*m+j));
            }
        }
    }

    printf("%d\n",ans);
    return 0;
}