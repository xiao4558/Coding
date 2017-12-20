//
// Created by xiao on 2017/11/21.
//

#include <stdio.h>
#include <string.h>

int main(){

    int m = 5, n;
    scanf("%d %d", &m, &n);

    int road[m+1];
    memset(road, 0, (m+1)* sizeof(int));

    for (int i = 0; i < n; ++i) {
        int start, end;
        scanf("%d %d", &start, &end);

        for (int j = start; j <= end; ++j) {
            road[j] = 1;
        }
    }

    int count = 0;
    for (int k = 0; k < m + 1; ++k) {
        if (road[k] == 1){
            count++;
        }
    }

    printf("%d", m +1 - count);

    return 0;
}