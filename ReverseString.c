//
// Created by Dell on 2017/12/1.
//
#include <stdio.h>

int main(){
    char string[500];
    int end = 0;
    scanf("%s", string);

    while (string[end] != '\0'){
        end++;
    }
    end--;
    while (end >= 0){
        printf("%c", string[end]);
        end--;
    }
    return 0;
}
