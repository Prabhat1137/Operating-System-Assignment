#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Exact 2 files needed!");
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {

        close(pipefd[0]);

        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            perror("fopen");
            return 1;
        }

        char c;
        int non_alphabetic_count = 0;
        while ((c = fgetc(file)) != EOF)
        {
            if (!isalpha(c))
            {
                non_alphabetic_count++;
            }
            write(pipefd[1], &c, 1);
        }

        fclose(file);

        close(pipefd[1]);

        printf("Total number of non alphabetic characters: %d", non_alphabetic_count);

        char count_str[10];
        sprintf(count_str, "%d", non_alphabetic_count);
        write(pipefd[1], count_str, strlen(count_str));
    }
    else
    {

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

        char count_str[10];
        int bytes_read = read(pipefd[0], count_str, sizeof(count_str));
        count_str[bytes_read] = '\0';

        fclose(file);
        close(pipefd[0]);
    }

    return 0;
}