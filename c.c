#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int main(){
    int ch;
    printf("Enter character :\n");
    while(((ch=getchar())!=EOF)){
        if(islower(ch)){
            ch=toupper(ch);
            putchar(ch);
            continue;
        }
        if(isupper(ch)){
            ch=tolower(ch);
            putchar(ch);
            continue;
        }else{
            putchar(ch);
        }
    }
    if(ch==0){
        exit(0);
    }
}