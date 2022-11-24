#include<cstdio>
#include<iostream>
#include<stdlib.h>
using namespace std;

int fun(char* str, int a[]){
    int cnt = 0;
    for(int i=0;str[i]!='\0';i++){
        if(str[i]>='0'&&str[i]<='9'){
            a[++cnt] = str[i] - '0';
        }
    }
    return cnt;
}

int main(){
    int a[1024];
    int len=fun("1234314abscdww123",a);
    for(int i=1;i<=len;i++){
        printf("%d",a[i]);
    }
    system("pause");
    return 0;
}