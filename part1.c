#include <stdio.h>
#include <string.h>
void pr_params(char **args)
{
    int i,j;
     for(i=0;args[i][0]!='1';i++){
        for(j=0;args[i][j]!='\n';j++){
            printf("%c",args[i][j]);

        }
        printf("\n");
    }
    
}
int main()
{
    int i,j,in=0;
    char s1[100];
    char s2[100];
    char s3[100];
    char *params[500];
    printf("enter the number of characters :");
    int n;
    scanf(" %d",&n);
     printf("enter %d characters :",n);
    for(i=0;i<n;i++){
        scanf(" %c",&s1[i]);
    }
    s1[i]='\n';
    params[in]=s1;
    in++;

    printf("enter the number of characters :");
    
    scanf(" %d",&n);
     printf("enter %d characters :",n);
     for(i=0;i<n;i++){
        scanf(" %c",&s2[i]);
    }
    s2[i]='\n';
    params[in]=s2;
    in++;

     printf("enter the number of characters :");
    
    scanf(" %d",&n);
     printf("enter %d characters :",n);
     for(i=0;i<n;i++){
        scanf(" %c",&s3[i]);
    }
    s3[i]='\n';
    params[in]=s3;
    in++;
    char x='1';
    params[in]=&x;
   
   pr_params(params);
   
  
   
}