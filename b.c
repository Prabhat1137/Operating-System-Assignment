#include <stdio.h>
#include <stdlib.h>
int main(){
    printf("Enter character, for EOF press ctr+D  flow by ctr +Z to stop :\n");
    
    int n;
    int count=0;
    while((n=getchar())!=EOF){
        if(((n>96)&& (n<123)) || ((n>64 && n<91))){
            continue;
        }else{
            putchar(n);
            count++;
        }

    }
    printf("\nTotal NON-alphabetic character printed is : %d ",count);
    if(n==0){
        exit(0);
    }
}