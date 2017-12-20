//
// Created by xiao on 2017/11/20.
//

#include <stdio.h>
#include <stdlib.h>

int compare (const void * a, const void * b){
    return *((int *)a) - *((int *)b);
}

int main(){
    int n, l;
    scanf("%d%d", &n, &l);

    int lamps[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &lamps[i]);
    }

    qsort(lamps, n, sizeof(int), compare);

    double max = lamps[0];
    for (int i = 0; i < n - 1; ++i) {
        if(max < 1.0*(lamps[i + 1] - lamps[i])/2){
            max = 1.0*(lamps[i + 1] - lamps[i])/2;
        }
    }

    if (max < l - lamps[n-1]){
        max = l - lamps[n-1];
    }

    printf("%.2f", max);
    return 0;
}