#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //if number of files not equal to 2
    if (argc != 3)
    {
        printf("Exact 2 files needed!");
        return 1;
    }

  // file descriptor is created

    int pipefd[2];
    //checking pipe is created or not
    if (pipe(pipefd) == -1)
    {
       printf("pipe not created");
        return 1;
    }

    //creating child
    // pid =0 for child
    // pid=-1 for not creation of child
    // pid>0 for parent
    pid_t pid = fork();
    // checking for creation of child or not
    if (pid == -1)
    {
        printf("\n child not created");
        return 1;
    }
     //condition for child process
    if (pid == 0)
    {
         // closing reading end of pipe
        close(pipefd[0]);
         // creating file pointer
        FILE *file = fopen(argv[1], "r");
        // checking for file is opened or not
        if (file == NULL)
        {
           printf("\nfile not opened");
            return 1;
        }

         // converting lower case to upper case and upper case to lower case
        char ch;
        int non_alphabetic_count = 0;
        while ((ch = fgetc(file)) != EOF)
        {
            if (isupper(ch))
            {
                ch = tolower(ch);
            }

            else if (islower(ch))
            {
                ch = toupper(ch);
            }

            if(!isalpha(ch))
            {
                non_alphabetic_count++;
            }
            // writing into pipe
            write(pipefd[1], &ch, 1);
        }
      

        printf("Number of non-alphabetic characters: %d ", non_alphabetic_count);
        
    }
    else
    {
         // closing writing end of pipe
        close(pipefd[1]);

        FILE *file = fopen(argv[2], "w");
        if (file == NULL)
        {
            perror("fopen");
            return 1;
        }

        char c;
        while (read(pipefd[0], &c, 1) > 0)
        {
            fputc(c, file);
        }
        printf("\nContents copied successfully");
        // closing file and pipe
        fclose(file);
        close(pipefd[0]);
    }

    return 0;
}