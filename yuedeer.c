//
// Created by xiao on 2017/11/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int N = 1000 + 5;

int main(){
    char *str = malloc(N), *sample = malloc(N), temp;

    scanf("%s", str);
    scanf("%s", sample);

    int length = strlen(str);
    int count = 0;

    for (int i = 0; i < length; ++i) {
        if ((str[i] >= '0' && str[i] <= '9') ||
                (str[i] >= 'a' && str[i] <= 'z') ||
                (str[i] >= 'A' && str[i] <= 'Z')){
            temp = '1';
        } else{
            temp = '0';
        }

        if (temp == sample[i]){
            count++;
        }
    }
    free(str);
    free(sample);

    printf("%.2f%%\n", count*100.00/length);
}