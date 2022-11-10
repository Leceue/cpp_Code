#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;
int f[2][1010][1010][2];//0:上,1:右 
char map[1010][1010];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",map[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) f[0][i][j][0]=f[0][i][j][1]=10000000;
	f[0][1][1][0]=f[0][1][1][1]=f[1][1][1][0]=f[1][1][1][1]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(map[i][j]=='#')
			{
				f[1][i][j][0]=f[1][i][j][1]=-1;
				f[0][i][j][0]=f[0][i][j][1]=10000000;
				continue;
			}
			f[0][i+1][j][0]=min(f[0][i+1][j][0],min(f[0][i][j][0],f[0][i][j][1]+1));
			f[0][i][j+1][1]=min(f[0][i][j+1][1],min(f[0][i][j][1],f[0][i][j][0]+1));
			f[1][i+1][j][0]=max(f[1][i+1][j][0],max(f[1][i][j][0],f[1][i][j][1]+1));
			f[1][i][j+1][1]=max(f[1][i][j+1][1],max(f[1][i][j][1],f[1][i][j][0]+1));
		}
	}
	if(f[0][n][m][0]>=1000000) puts("-1");
	else printf("%d %d",max(f[1][n][m][0],f[1][n][m][1])-1,min(f[0][n][m][0],f[0][n][m][1]));
	
	return 0;
}