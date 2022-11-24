/*题目:函数str count统计子字符串substr在字符串str中出现的次数，如果substr在str中不出现，则返回值0。请完成该函数。
输出结果见图:样张JPG*/

#include<iostream>
#include<cstring>
using namespace std;
/********Program********/

int str_count(char substr[],char str[]) 
{

	int count=0;
	int k,j;
	char *ss=substr;
	char *s=str;
	for(int i=0;s[i]!='\0';i++)
	{
		for(j=i,k=0;ss[k]==s[j]&&s[j]!='\0';k++,j++)
		{
			if(ss[k+1]=='\0')
			count++;
		}
	}
	return count;
}
/********End********/
int main(void)
{
    char ss[100];
    char* s = "ABCDabcd1234+- */XYZxyz/ABCDabcd1234+-*/Aa1 ABCDabed";
    cout<<"母串="<<s<<endl;
    cout<< "待计数子串=";
    cin.getline(ss,99);
    cout<<"子串在母串中共出现" <<str_count(ss,s)<< "次" <<endl;
    return 0;
}

