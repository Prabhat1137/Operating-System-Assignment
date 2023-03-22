#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <setjmp.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

static sigjmp_buf buf;
static int alarm_time = 0;

// allow parent to continue

void alarm_handler(int signo)
{
    siglongjmp(buf, 1);
}

int main(int argc, char *argv[])
{
    //int option_n = 0;
    int file_count = 0;
    char *file1 = NULL;
    char *file2 = NULL;

    // parse command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            alarm_time = atoi(optarg);
            break;
        default:
            printf(" 2 files argumnets needed");
            return 1;
        }
    }

    file_count = argc - optind;
    if (file_count > 0)
    {
        file1 = argv[optind];
    }
    if (file_count > 1)
    {
        file2 = argv[optind + 1];
    }

    if (alarm_time > 0)
    {
        signal(SIGALRM, alarm_handler);
        alarm(alarm_time);
    }

    if (file_count == 1)
    {
        //system call to open file
        int fd = open(file1, O_RDONLY);
        if (fd < 0)
        {
            printf("file not opened");
            return 1;
        }
        // create duplicate file
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            printf("dup not created");
            return 1;
        }
        // closing file descriptor
        close(fd);
    }
    else if (file_count == 2)
    {
        if (sigsetjmp(buf, 1) != 0)
        {
            printf("Time limit exceeded.\n");
            return 0;
        }
        // create pipe
        int pipefd[2];
        if (pipe(pipefd) == -1)
        {
            printf("pipe not created");
            return 1;
        }

        pid_t pid = fork();
        if (pid == -1)
        {
           printf("\n child not created");
            return 1;
        }

        if (pid == 0)
        {
            // child process
            // close read end of pipe
            close(pipefd[0]); 
            // file pointer opened
            FILE *file = fopen(file1, "r");
            if (file == NULL)
            {
               printf("\nfile not opened");
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
            printf("Number of non-alphabetic characters: %d", non_alphabetic_count);

            char count_str[10];
            printf(count_str, "%d", non_alphabetic_count);
            write(pipefd[1], count_str, strlen(count_str));
        }
        else
        {
            // parent process
            // close write end of pipe
            close(pipefd[1]); 
            FILE *file = fopen(file2, "w");
            if (file == NULL)
            {
                printf("\nfile not opened");
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
            
            // closing file pointer and pipe reading end
            fclose(file);
            close(pipefd[0]); 
        }
    }
    return 0;
}