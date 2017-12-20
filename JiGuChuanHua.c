//
// Created by xiao on 2017/11/21.
//

#include <stdio.h>

int func(int time, int num);

int n, m;

int main(){

    scanf("%d %d", &n, &m);

    int result = func(m, 0);
    printf("%d", result);

    return 0;
}

int func(int time, int num){
    if(time == 1){
        if(num == 1 || num == n - 1){
            return 1;
        } else{
            return 0;
        }
    }

    return func(time - 1, (num + n -1)%n) + func(time - 1, (num + 1)%n);
}