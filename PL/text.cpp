#include "./vector.h"
#include<cstdio>
#include<stdlib.h>
#include<iostream>
using namespace mystl;
int s = 1;

int main() {
    int size = 5;
    vector_<int> a(5);
    a.push_back(s);
    printf("%d\n",a.size());
    system("pause");
    return 0;
}