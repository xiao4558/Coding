//
// Created by Dell on 2017/11/29.
//

#include <stdio.h>

int main(){

    int n;
    scanf("%d", &n);

    int remain = 0;
    int count = 0;

    while (n != 0){
        remain = n % 2;
        if (remain == 1){
            count++;
        }
        n = n/2;

    }

    printf("%d", count);

    return 0;
}