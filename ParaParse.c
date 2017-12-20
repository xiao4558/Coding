//
// Created by Dell on 2017/12/1.
//

//如果split为空格，如果遇到空格的话就输出\n，然后continue，如果遇到引号的话，则将split改为引号，然后continue
//如果split为引号，遇到空格则忽略，遇到引号则将split改为空格，然后continue

#include <stdio.h>
#include <malloc.h>

int main(){
    char * string = (char *)malloc(100);
    fgets(string, 100, stdin);

    char split = ' ', current;
    int index = 0;
    while (string[index] != '\0'){
        current = string[index];
        if (split == ' ' && current == ' '){
            printf("\n");
        } else if (split == ' ' && current == '\"'){
            split = '\"';
        } else if (split == '\"' && current == '\"'){
            split = ' ';
        } else{
            printf("%c", current);
        }
        index++;
    }
    return 0;
}


