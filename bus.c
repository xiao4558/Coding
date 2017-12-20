//
// Created by xiao on 2017/11/20.
//

#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);

    int num = 0;

    int max = 0;

    int up, down;

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &down, &up);

        num = num - down + up;

        if (num > max){
            max = num;
        }

    }

    printf("%d", max);
}