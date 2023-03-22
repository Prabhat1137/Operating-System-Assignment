#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
   int i;
   int count = 0;
   if (argc == 1)
   {
      printf(" No string encountered !\n");
      //exit(1);
   }

  if(argc>1)
   {
      
      for (i = 1; i < argc; i++)
      {
         if (argv[i][0] == '-')
         {
            count++;
            // continue;
         }
         else
         {
            printf("%s\n", argv[i]);
         }
      }
      if (count == argc)
      {
         printf("Nothing to print\n");
      }
   }
}