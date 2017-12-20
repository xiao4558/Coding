//
// Created by Dell on 2017/11/30.
//

#include <stdio.h>

int main(){

    int n;
    scanf("%d",&n);
    if (n == 0){
        printf("0");
    }

    int remain = 0;
    while (n != 0){
        remain = n % 10;
        printf("%d", remain);
        n = n / 10;
    }


    return 0;
}