//
// Created by Dell on 2017/11/24.
//

#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int t;
        scanf("%d", &t);
        int data[t];
        for (int j = 0; j < t; ++j) {
            scanf("%d", &data[j]);
        }

        int flag[t];
        memset(flag, 1, t* sizeof(int));
        for (int k = 0; k < t; ++k) {
            for (int j = k + 1; j < t; ++j) {
                if (data[j] < data[k] && flag[k] + 1 > flag[j]){
                    flag[j] = flag[k] + 1;
                }
            }
        }

        int max = 0;
        for (int l = 0; l < t; ++l) {
            if (flag[l] > max){
                max = flag[l];
            }
        }

        printf("%d", max);
    }
    return 0;
}

