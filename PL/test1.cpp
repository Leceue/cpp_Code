#include<cstdio>
#include<stdlib.h>
using namespace std;

int main(){
    char s;
    scanf("%c",s);
    int n=s-'0';
    if(n>0&&n<=9){
        while(n--){
            printf("*");
        }
    }else {
        printf("请输入非零的数字");
    }
    return 0;
}
