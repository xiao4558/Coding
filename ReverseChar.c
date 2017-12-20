//
// Created by Dell on 17/12/12.
//

#include <stdio.h>

int main(){

    char string[500];
    fgets(string, 500, stdin);

    int lengh = 0;
    while (string[lengh] != '\0') lengh++;

    lengh = lengh - 2;
    while (lengh >= 0){
        printf("%c", string[lengh]);
        lengh--;
    }

    return 0;
}