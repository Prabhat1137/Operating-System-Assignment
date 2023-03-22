#include <stdio.h>
#include <stdlib.h>
int main(){
    printf("hello\n");
    
    FILE *file;
    file=fopen("E:\\E Drive\\IIITG Study\\Semester\\SEM 4\\operating system lab\\Lab2\\include\\ctype.h\\b.txt","r");
    int n;
    int count=0;
    while((n=getc(file))!=EOF){
        if(((n>96)&& (n<123)) || ((n>64 && n<91))){
            continue;
        }else{
            putchar(n);
            count++;
        }

    }
    printf("\nTotal NON-alphabetic character printed is : %d ",count);
}