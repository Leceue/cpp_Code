#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#define maxn 1007
using namespace std;
int n,m,f[maxn][maxn][2],g[maxn][maxn][2],sc[maxn][maxn],vis[maxn][maxn];

template<typename type_of_scan>
void scan(type_of_scan &x){
    type_of_scan f=1;char s=getchar();x=0;
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}

int main(){
    memset(f,127,sizeof(f));
    memset(g,128,sizeof(g));
    scan(n),scan(m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char s=getchar();
            while(s=='\n') s=getchar();
            if(s!='#') sc[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            printf("%d",sc[i][j]);
        }
        puts("");
    }
    f[1][1][0]=f[1][1][1]=0;
    g[1][1][0]=g[1][1][1]=0;
    vis[1][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!sc[i][j]||!vis[i][j]) continue;
            if(sc[i][j+1]){
                f[i][j+1][0]=min(f[i][j][0],f[i][j][1]+1);
                g[i][j+1][0]=max(g[i][j][0],g[i][j][1]+1);
                vis[i][j+1]=1;
            }
            if(sc[i+1][j]){
                f[i+1][j][1]=min(f[i][j][1],f[i][j][0]+1);
                g[i+1][j][1]=max(g[i][j][1],g[i][j][0]+1);
                vis[i+1][j]=1;
            }
        }
    }
    if(!vis[n][m]) printf("-1\n");
    else printf("%d %d\n",max(g[n][m][0],g[n][m][1])-1,min(f[n][m][0],f[n][m][1]));
    system("pause");
    return 0;
}