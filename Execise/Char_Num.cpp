/*��Ŀ:����str countͳ�����ַ���substr���ַ���str�г��ֵĴ��������substr��str�в����֣��򷵻�ֵ0������ɸú�����
��������ͼ:����JPG*/

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
    cout<<"ĸ��="<<s<<endl;
    cout<< "�������Ӵ�=";
    cin.getline(ss,99);
    cout<<"�Ӵ���ĸ���й�����" <<str_count(ss,s)<< "��" <<endl;
    return 0;
}

