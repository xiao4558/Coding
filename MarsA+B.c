//
// Created by xiao on 2017/11/15.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(){
    char a[100], b[100];

    while(true){
        scanf("%s%s", a, b);
        if (a == "0" && b == "0"){
            break;
        }

        for (int i = 0; i < 80; ++i) {
            a[i] = 0;
        }


    }

    return 0;
}
