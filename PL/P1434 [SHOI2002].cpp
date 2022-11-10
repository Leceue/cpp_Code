#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stdlib.h>
#include<iostream>
using namespace std;
int n,m,x,y,maxn;
int sc[107][107],f[107][107];
int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};
int ans=0;

// template <typename type_of_scan>
// void scan(type_of_scan &x){
//     type_of_scan f=1;char s=getchar();x=0;
//     while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
//     while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
//     x*=f;
// }

struct node{
    int x,y,w;
}srt[10007];

bool cmp(node a,node b){
    return a.w>b.w;
}
queue<node> q;
int l=0;
int mi=0;

void dfs(){
    if(!l) return ;
    for(int i=1;i<=l;i++){
        x=srt[i].x,y=srt[i].y;
        int w=srt[i].w;
        for(int j=0;j<8;j++){
            int xd=x+dir[j][0],yd=y+dir[j][1];
            if(sc[xd][yd]>w) continue;
            if(!f[xd][yd]) q.push((node){xd,yd,sc[xd][yd]});
            f[xd][yd]=max(f[xd][yd],f[x][y]+1);
            ans=max(ans,f[xd][yd]);
        }
        cerr<<++mi<<endl;
    }
    l=0;
    while(!q.empty()){
        srt[++l]=q.front();
        q.pop();
    }
    sort(srt+1,srt+1+l,cmp);
    dfs();
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&sc[i][j]);
            if(sc[i][j]>maxn){
                maxn=sc[i][j];
                x=i,y=j;
            }
        }
    }
    f[x][y]=1;
    srt[++l]=(node){x,y,sc[x][y]};
    dfs();
    printf("%d",ans);
    system("pause");
    return 0;
}