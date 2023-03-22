#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define MAX_PROCESS 50

typedef struct
{
    char *name;
    int arrival;
    int cpuburst;
    int turnaround;
    int wait;
} Process;
int p = 0;

void selection_sort(Process processtable[])
{
    int i = 0;
    int j = 0;
    int min = 0;
    for (i = 0; i < p; i++)
    {
        min = i;
        for (j = i + 1; j < p; j++)
        {
            if (processtable[j].cpuburst < processtable[min].cpuburst)
            {
                Process p = processtable[j];
                processtable[j] = processtable[min];
                processtable[min] = p;
            }
        }
        // printf("%d ",processtable[i].cpuburst);
    }
}

void selection_sort_arrival(Process processtable[])
{
    int i = 0;
    int j = 0;
    int min = 0;

    for (i = 0; i < p; i++)
    {
        min = i;
        for (j = i + 1; j < p; j++)
        {

            if (processtable[j].arrival < processtable[min].arrival)
            {
                Process p = processtable[j];
                processtable[j] = processtable[min];
                processtable[min] = p;
            }
        }
    }
}

Process processtable[MAX_PROCESS];
void clearProcessTable()
{
    int i = 0;
    for (i = 0; i < p; i++)
    {
        processtable[i].arrival = 0;
        processtable[i].cpuburst = 0;
        processtable[i].name = 0;
        processtable[i].turnaround = 0;
        processtable[i].wait = 0;
    }
}

void ReadProcessTable(char *filename)
{
    p = 0;
    FILE *ptr;
    ptr = fopen(filename, "r");
    if (ptr == NULL)
    {
        printf("\nCan not open file");
        exit(1);
    }

    int completion_time = 0;
    char str[50];
    while (fgets(str, 30, ptr) != NULL)
    {

        char *ch;
        ch = strtok(str, " ");
        int choice = 1;

        while (ch != NULL)
        {
            switch (choice)
            {
            case 1:
            {
                processtable[p].name = malloc(2 * sizeof(char));
                strcpy(processtable[p].name, ch);
                choice++;
                ch = strtok(NULL, " ");
                break;
            }
            case 2:
            {
                processtable[p].arrival = ((int)*ch - 48);
                choice++;
                ch = strtok(NULL, " ");
                break;
            }
            case 3:
            {

                processtable[p].cpuburst = ((int)*ch - 48);
                choice++;
                ch = strtok(NULL, " ");
                break;
            }
            }
        }
        p++;
    }
}

void PrintProcessTable()
{
    printf("\n\nPrinting process table :");
    int i;
    for (i = 0; i < p; i++)
    {
        printf("\n");
        printf("%s ", processtable[i].name);
        printf("%d ", processtable[i].arrival);
        printf("%d ", processtable[i].cpuburst);
    }
}

void FCFS()
{
    int current_time = 0;
    int completion_time = 0;
    int i, j;
    int min;
    printf("\n----------------------------------------------------------\n");
    printf("FCFS running :\n");
    printf("----------------------------------------------------------\n");
    for (i = 0; i < p; i++)
    {
        min = i;
        for (j = i + 1; j < p; j++)
        {

            if (processtable[j].arrival < processtable[min].arrival)
            {
                Process p = processtable[j];
                processtable[j] = processtable[min];
                processtable[min] = p;
            }
        }

        if (i == 0)
        {
            completion_time = processtable[i].arrival + processtable[i].cpuburst;
            processtable[i].turnaround = completion_time - processtable[i].arrival;
            processtable[i].wait = processtable[i].turnaround - processtable[i].cpuburst;
            printf("\n[%d - %d]       %s     running :", processtable[i].arrival, completion_time, processtable[i].name);
            current_time = completion_time;
            continue;
        }
        if (i > 0 && processtable[i].arrival <= current_time)
        {
            completion_time = current_time + processtable[i].cpuburst;
            processtable[i].turnaround = completion_time - processtable[i].arrival;
            processtable[i].wait = processtable[i].turnaround - processtable[i].cpuburst;
            printf("\n[%d - %d]       %s     running :", current_time, completion_time, processtable[i].name);
            current_time = completion_time;
        }
        else
        {

            completion_time = processtable[i].arrival + processtable[i].cpuburst;
            processtable[i].turnaround = completion_time - processtable[i].arrival;
            processtable[i].wait = processtable[i].turnaround - processtable[i].cpuburst;
            printf("\n[%d - %d]       %s     running :", current_time, completion_time, processtable[i].name);
            current_time = completion_time;
        }
    }
    float sum_turn = 0;
    float sum_wait = 0;
    printf("\n\nTurnaround times : ");
    for (i = 0; i < p; i++)
    {
        printf("%s[%d]  ", processtable[i].name, processtable[i].turnaround);
        sum_turn += processtable[i].turnaround;
    }

    printf("\n\nWaiting times    : ");
    for (i = 0; i < p; i++)
    {
        printf("%s[%d]  ", processtable[i].name, processtable[i].wait);
        sum_wait += processtable[i].wait;
    }

    printf("\n\nAverage turnaround time : %f", sum_turn / p);
    printf("\nAverage wait time       : %f", sum_wait / p);
}
void PrintStatistics()
{
    printf("\n\nProcess Statistics:");
    int i;
    for (i = 0; i < p; i++)
    {
        printf("\n");
        printf("%s ", processtable[i].name);
        printf("%d ", processtable[i].arrival);
        printf("%d ", processtable[i].cpuburst);
        printf("%d ", processtable[i].turnaround);
        printf("%d ", processtable[i].wait);
    }
}

void RR(int quantum)
{
    int min;
    printf("\n----------------------------------------------------------\n");
    printf("Round Robin(RR) running :\n");
    printf("----------------------------------------------------------\n");

    int i = 0;
    int j = 0;
    int c_burst[p];
    selection_sort_arrival(processtable);
    int current_time = 0;
    int completion_time = 0;
    int count = 0;
    int gcount=0;
    current_time = processtable[0].arrival;

    for (i = 0; i < p; i++)
    {
        c_burst[i] = processtable[i].cpuburst;
        printf("%d ",processtable[i].cpuburst);
    }

    while (1)
    {
        count = 0;
        for (i = 0; i < p; i++)
        {
            if (processtable[i].cpuburst == 99999)
            {
                count++;
            }
        }

        if (count == p)
        {
            break;
        }
   
    For:
        count = 0;
       
        for (i = 0; i < p; i++)
        {
            if (processtable[i].cpuburst == 99999 && processtable[i].arrival <= current_time)
            {
                
                if (gcount == (count))
                {
                    current_time = processtable[i + 1].arrival;
                }
                count++;
            }
            if (processtable[i].cpuburst != 99999 && processtable[i].arrival <= current_time)
            {

                if (processtable[i].cpuburst >= quantum)
                {
                    if (processtable[i].cpuburst == quantum)
                    {

                        completion_time = current_time + processtable[i].cpuburst;
                        processtable[i].turnaround = completion_time - processtable[i].arrival;
                        printf("\n[%d - %d]       %s     running :", current_time, completion_time, processtable[i].name);

                        current_time = completion_time;
                        processtable[i].cpuburst = 99999;
                        gcount++;
                    }
                    else
                    {
                        completion_time = current_time + quantum;
                        processtable[i].turnaround = completion_time - processtable[i].arrival;
                        processtable[i].cpuburst -= quantum;
                        printf("\n[%d - %d]       %s     running :", current_time, completion_time, processtable[i].name);

                        current_time = completion_time;
                       
                    }
                }
                else
                {
                    printf("%d",current_time);
                    completion_time = current_time + processtable[i].cpuburst;
                    processtable[i].turnaround = completion_time - processtable[i].arrival;
                    printf("\n[%d - %d]       %s     running :", current_time, completion_time, processtable[i].name);

                    current_time = completion_time;
                    processtable[i].cpuburst = 99999;

                    gcount++;
                }
            }
            else
            {
                if (processtable[i].cpuburst != 99999 && processtable[i].arrival > current_time)
                {
                   
                    goto For;
                }
            }
        }
    }

    for (i = 0; i < p; i++)
    {
        processtable[i].cpuburst = c_burst[i];
        printf("%d ",c_burst[i]);
    }

    for (i = 0; i < p; i++)
    {
        processtable[i].wait = (processtable[i].turnaround - processtable[i].cpuburst);
    }

    float sum_turn = 0;
    float sum_wait = 0;
    printf("\n\nTurnaround times : ");
    for (i = 0; i < p; i++)
    {
        printf("%s[%d]  ", processtable[i].name, processtable[i].turnaround);
        sum_turn += processtable[i].turnaround;
    }

    printf("\n\nWaiting times    : ");
    for (i = 0; i < p; i++)
    {
        printf("%s[%d]  ", processtable[i].name, processtable[i].wait);
        sum_wait += processtable[i].wait;
    }

    printf("\n\nAverage turnaround time : %f", sum_turn / p);
    printf("\nAverage wait time       : %f", sum_wait / p);
}

void SRBF()
{
    printf("\n----------------------------------------------------------\n");
    printf("SRBF running :\n");
    printf("----------------------------------------------------------\n");
    static int current_time = 0;
    static int completion_time = 0;

    int i = 0;
    int j = 0;
    int k = 0;
    int min = 0;

    int c_arrival[p];
    int c_burst[p];
    selection_sort_arrival(processtable);
    for (i = 0; i < p; i++)
    {
        c_burst[i] = processtable[i].cpuburst;
    }
    for (i = 0; i < p; i++)
    {
        c_arrival[i] = processtable[i].arrival;
    }

    for (i = 0; i < p; i++)
    {
        min = i;
        for (j = i + 1; j < p; j++)
        {
            if (c_arrival[j] < c_arrival[min])
            {
                int p = c_arrival[j];
                c_arrival[j] = c_arrival[min];
                c_arrival[min] = p;
            }
        }
    }

    current_time = c_arrival[0];

    while (1)
    {
        int count = 0;
        int flag = 0;
        selection_sort(processtable);

        for (i = 0; i < p; i++)
        {
            if (processtable[i].cpuburst == 99999)
            {
                count++;
            }
        }
        if (count == p)
        {
            break;
        }

        if (processtable[0].cpuburst == 0)
        {
            processtable[0].cpuburst = 99999;
            continue;
        }
        int arrival = 0;
        for (i = 0; i < p; i++)
        {
            if (processtable[i].cpuburst != 99999)
            {
                arrival = processtable[i].arrival;
                break;
            }
        }

        int carrival = 0;
        for (i = 0; i < p; i++)
        {
            if (processtable[i].arrival < arrival && processtable[i].cpuburst != 99999)
            {
                for (j = 0; j < p; j++)
                {
                    if (processtable[i].arrival == c_arrival[j])
                    {
                        carrival = c_arrival[j];
                        break;
                    }
                }
                int end = current_time + processtable[i].cpuburst;
                if (end <= c_arrival[j + 1])
                {
                    if (end == c_arrival[j + 1])
                    {
                        completion_time = end;
                        processtable[i].turnaround = completion_time - processtable[i].arrival;
                        processtable[i].cpuburst = 0;

                        printf("\n[%d - %d]       %s     running :", current_time, completion_time, processtable[i].name);

                        current_time = completion_time;
                        flag = 1;
                    }
                    if (end < c_arrival[j + 1])
                    {
                        completion_time = current_time + processtable[i].cpuburst;
                        processtable[i].turnaround = completion_time - processtable[i].arrival;
                        processtable[i].cpuburst = 0;

                        printf("\n[%d - %d]       %s     running :", current_time, completion_time, processtable[i].name);

                        current_time = c_arrival[j + 1];
                        flag = 1;
                    }
                }
                if (end > c_arrival[j + 1])
                {
                    for (k = 0; k < p; k++)
                    {
                        if (processtable[k].arrival == c_arrival[j + 1])
                        {
                            int rem = processtable[i].cpuburst - (c_arrival[j + 1] - c_arrival[j]);
                            if (processtable[k].cpuburst < rem)
                            {
                                processtable[i].cpuburst = rem;
                                completion_time = c_arrival[j + 1];

                                printf("\n[%d - %d]       %s     running :", current_time, completion_time, processtable[i].name);

                                current_time = completion_time;
                                flag = 1;
                                break;
                            }
                            else
                            {
                            }
                        }
                    }
                }
            }
        }

        if (processtable[0].cpuburst != 99999 && flag == 0)
        {
            for (j = 0; j < p; j++)
            {
                if (arrival == c_arrival[j] && processtable[i].cpuburst != 99999)
                {
                    carrival = c_arrival[j];
                    break;
                }
            }

            int executione_time = 0;
            if (j < p - 1)
            {
                executione_time = (c_arrival[j + 1] - c_arrival[j]);
            }

            int burst = processtable[0].cpuburst;
            completion_time = current_time + processtable[0].cpuburst;
            processtable[0].turnaround = completion_time - processtable[0].arrival;
            processtable[0].cpuburst = 0;
            printf("\n[%d - %d]       %s     running :", current_time, completion_time, processtable[0].name);

            if (burst >= executione_time)
            {
                current_time = completion_time;
            }
            if (burst < executione_time)

            {
                current_time += executione_time;
            }
        }
    }

    selection_sort_arrival(processtable);
    for (i = 0; i < p; i++)
    {
        processtable[i].cpuburst = c_burst[i];
    }

    for (i = 0; i < p; i++)
    {
        processtable[i].wait = processtable[i].turnaround - processtable[i].cpuburst;
    }

    float sum_turn = 0;
    float sum_wait = 0;
    printf("\n\nTurnaround times : ");
    for (i = 0; i < p; i++)
    {
        printf("%s[%d]  ", processtable[i].name, processtable[i].turnaround);
        sum_turn += processtable[i].turnaround;
    }

    printf("\n\nWaiting times    : ");
    for (i = 0; i < p; i++)
    {
        printf("%s[%d]  ", processtable[i].name, processtable[i].wait);
        sum_wait += processtable[i].wait;
    }

    printf("\n\nAverage turnaround time : %f", sum_turn / p);
    printf("\nAverage wait time       : %f", sum_wait / p);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    /* code */

    if (argc == 1)
    {
        printf("\n file(txt) is not passed :\n");
        exit(0);
    }

    if (argc == 2)
    {
        int terminate = 1;

        while (terminate == 1)
        {
            int choice = 0;
            printf("\n----------------------------------------------------------\n");
            printf("CPU Scheduling Simulation :\n");
            printf("----------------------------------------------------------\n");
            printf("\nSelect the scheduling algorithm [1,2,3 or 4]:");
            printf("\n1. First Come First Served (FCFS)");
            printf("\n2. Round Robin (RR)");
            printf("\n3. SRBF");
            printf("\n4. Exit");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
            {
                ReadProcessTable(argv[1]);
                PrintProcessTable();
                FCFS();
                PrintStatistics();

                break;
            }
            case 2:
            {
                clearProcessTable();
                ReadProcessTable(argv[1]);
                PrintProcessTable();
                int n = 2;
                RR(n);
                PrintStatistics();

                break;
            }
            case 3:
            {
                clearProcessTable();
                ReadProcessTable(argv[1]);
                PrintProcessTable();
                SRBF();
                PrintStatistics();

                break;
            }
            case 4:
            {
                exit(0);
                break;
            }
            default:
            {
                printf("\nplease provide correct information");
                break;
            }
            }

            printf("\n\npress any key to continue...");

            getch();
        }
    }

    return 0;
}
