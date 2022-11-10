#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#define maxn 1000000007
using namespace std;

int n,m,minx=maxn*2,maxx,p,lim;
int sc[50007][2];

template<typename type_of_scan>
void scan(type_of_scan &x){
    type_of_scan f=1;char s=getchar();x=0;
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}

struct tree{
    int le,ri,w1,w2;
}tr[500007];

struct re{
    int x,y;
};

re max(re a,re b){
    return (re){max(a.x,b.x),max(a.y,b.y)};
}

int max(int x,int y){
    return x>y?x:y;
}

void add(int l,int r,int space,int &root,int k){
    if(!root) root=++p;
    if(l==r){
        tr[root].w1=k;
        tr[root].w2=k;
        return ;
    }
    int mid=(l+r)>>1;
    if(mid>=space) add(l,mid,space,tr[root].le,k);
    else add(mid+1,r,space,tr[root].ri,k);
    if(!tr[root].le||!tr[root].ri) tr[root].w1=maxn;
    else tr[root].w1=max(tr[tr[root].le].w1,tr[tr[root].ri].w1);
    tr[root].w2=max(tr[tr[root].le].w2,tr[tr[root].ri].w2);
}

re query(int nl,int nr,int l,int r,int root){
    if(!root) return (re){maxn,0};
    if(nl<=l&&r<=nr) return (re){tr[root].w1,tr[root].w2};
    re re_ans=(re){0,0};
    int mid=(l+r)>>1;
    if(nl<=mid) re_ans=max(query(nl,nr,l,mid,tr[root].le),re_ans);
    if(mid<nr) re_ans=max(query(nl,nr,mid+1,r,tr[root].ri),re_ans);
    return re_ans;
}

// if(nl<=mid) re_ans=(re){max(query(nl,nr,l,mid,tr[root].le).x,re_ans.x),max(query(nl,nr,l,mid,tr[root].le).y,re_ans.y)};
//     if(mid<nr) re_ans=(re){max(query(nl,nr,mid+1,r,tr[root].ri).x,re_ans.x),max(query(nl,nr,mid+1,r,tr[root].ri).y,re_ans.y)};

int main(){
    int root=0;
    scan(n);
    for(int i=1;i<=n;i++){
        scan(sc[i][0]),scan(sc[i][1]);
        sc[i][0]+=maxn;
        minx=min(sc[i][0],minx);
        maxx=max(sc[i][0],maxx);
    }
    lim=maxx-minx+1;
    for(int i=1;i<=n;i++){
        sc[i][0]-=minx-1;
        add(1,lim,sc[i][0],root,sc[i][1]);
    }
    scan(m);
    for(int i=1;i<=m;i++){
        int y,x;
        scan(y),scan(x);
        re d=query(y+maxn-minx+2,x+maxn-minx,1,lim,root);
        re e=query(x+maxn-minx+1,x+maxn-minx+1,1,lim,root);
        if(d.y>=e.x) printf("false\n");
        else if(d.x==maxn) printf("maybe\n");
        else if(e.x>d.x) printf("true\n");
    }
    system("pause");
    return 0;
}

/*
6
2002 4920
2003 5901
2004 2832
2005 3890
2007 5609
2008 3024
1
2003 2007
*/