#include <stdio.h>
#include <string.h>
#include<stdlib.h>
void pr_params(char **args,int nargs)
{
    int i,j;
     for(i=0;i<nargs;i++){
        for(j=0;args[i][j]!='\n';j++){
            printf("%c",args[i][j]);

        }
        printf("\n");
    }
    
}
int main()
{
    int i,j,in=0;
    //char s[100];
    char *s;
    char *params[500];
   printf("Enter number of strings :");
   int ns;
   scanf(" %d",&ns);
   for(j=0;j<ns;j++){
     printf("enter the number of character of %dth string:",(j+1));
    int n;
    scanf(" %d",&n);
    
    s=(char *)malloc((sizeof(char)*100));
     printf("enter %d characters :",n);
    for(i=0;i<n;i++){
        
        scanf(" %c",&s[i]);
    }
    s[i]='\n';
    params[in]=s;
    in++;
   }
   
     pr_params(params,in);
   
  
   
}