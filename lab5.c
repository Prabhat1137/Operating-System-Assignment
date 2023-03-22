#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define number_of_process 5

// structure of processes
typedef struct
{
    char *name;
    int *allocated_resorce;
    int *request_resource;
    int flag;
   

} process;
// creating 5 process using array of process
process process_table[5];
// instances of resorces
int instance[3] = {8, 6, 9};

// 2D array of allocated process
int allcoate[][3] = {{0, 1, 0},
                     {1, 0, 2},
                     {1, 3, 1},
                     {0, 0, 1},
                     {4, 2, 3}};

// 2D array of request process
int request[][3] = {{1, 1, 0},
                    {1, 2, 3},
                    {3, 1, 1},
                    {0, 0, 1},
                    {3, 2, 2}};


void print_request_for_process(int p)
{
    int i;
   
    printf("\n");
    for(i=0;i<3;i++){
        printf("R%d ",i);
    }
     printf("\n");
    for(i=0;i<3;i++){
        printf("%d  ",allcoate[p][i]);
        
    }

}
// function to print available instnace in global instance array/resorces
void print_instance()
{
    int i;
    printf("\nAvailable instances:\n");
    for (i = 0; i < 3; i++)
    {
        printf("R%d ", i);
    }
    printf("\n");
    for (i = 0; i < 3; i++)
    {
        printf("%d  ", instance[i]);
    }
    printf("\n");
}

// function to allocate instances to the processes if sufficient instaces are available in allocating 2D array
void instance_allocation()
{
    int i, j;

    for (i = 0; i < number_of_process; i++)
    {
        process_table[i].name = (char *)malloc(2 * sizeof(char));
        process_table[i].allocated_resorce = malloc(3 * sizeof(int));
        process_table[i].request_resource = malloc(3 * sizeof(int));

        process_table[i].name = "p";
        for (j = 0; j < 3; j++)
        {
            if (allcoate[i][j] <= instance[j])
            {
                process_table[i].allocated_resorce[j] = allcoate[i][j];
                instance[j] -= allcoate[i][j];
            }
            else
            {
                printf("Instances of resources are not available...");
                printf("\nAvailable instances:");
                print_instance();
                printf("\nRequested instances:");
                print_request_for_process(i);
               
                exit(1);
            }
        }
    }
}

// function to initilize the request array for each process
void instance_request()
{
    int i, j;

    for (i = 0; i < number_of_process; i++)
    {

        for (j = 0; j < 3; j++)
        {

            process_table[i].request_resource[j] = request[i][j];
        }
    }
}

// checking for available process
int is_available(int i)
{
    int j;
    int count = 0;
    if (process_table[i].flag == 1)
    {
        
        return 0;
    }
    for (j = 0; j < 3; j++)
    {
        if (process_table[i].request_resource[j] <= instance[j])
        {
            count++;
        }
        else
        {
           // printf("0");
            return 0;
        }
    }

    if (count == 3)
    {
        //printf("1");
        return 1;
    }
//    if(process_table[i].flag==0)
//    {
//    printf("1");
//      return 1;
//    }
}



int remove_process()
{
    int i, j;
    int sum_ins = 99999;
    int curr_ins_sum = 0;
    int track_process = -1;
    int flag = 0;

    for (i = 0; i < number_of_process; i++)
    {
        curr_ins_sum = 0;
        if (process_table[i].flag==0)
        {
            //printf("isavailable");
            for (j = 0; j < 3; j++)
            {
                curr_ins_sum += process_table[i].allocated_resorce[j]+process_table[i].request_resource[j];
            }

            if (curr_ins_sum < sum_ins)
            {
                sum_ins = curr_ins_sum;
                track_process = i;
                flag = 1;
               // printf("flag 1");
            }
        }
    }

    if (flag == 1 && track_process != -1)
    {
        //printf("updating instance");
        process_table[track_process].flag = 1;
        for (j = 0; j < 3; j++)
        {
            instance[j] += process_table[track_process].allocated_resorce[j];
        }
        return track_process;
    }
}
// executing each process if sufficient instances are available in global instance array
void execute_process()
{
    int i, j;
    static int count_executed_process = 0;
    static int removed_process = 0;
start:
    while ((count_executed_process + removed_process) != number_of_process)
    {
        int flag2 = 0;
        int count = 0;
        static int step_count = 0;
        for (i = 0; i < number_of_process; i++)
        {

            int flag = 0;

            if (is_available(i))
            {
                int req[3];
                int allco[3];
                for (j = 0; j < 3; j++)
                {
                    instance[j] += process_table[i].allocated_resorce[j];
                    allco[j] = process_table[i].allocated_resorce[j];
                    process_table[i].allocated_resorce[j] += process_table[i].request_resource[j];
                    req[j] = process_table[i].request_resource[j];
                    process_table[i].request_resource[j] = 0;
                    process_table[i].flag = 1;
                    process_table[i].allocated_resorce[j] = 0;
                }
                step_count++;
                printf("\nstep %d: process p%d allocated instance %d %d %d and request instance %d %d %d allocated successfully", step_count, i, allco[0], allco[1], allco[2], req[0], req[1], req[2]);
                print_instance();

                count_executed_process++;
                flag = 1;
            }
            else
            {
                count++;
            }

            if (count == number_of_process && flag == 0)
            {
                step_count++;
                printf("\nstep %d:",step_count);
                printf("\ndeadlock occur...\nRemoving smallest process...\n");
                flag2 = 1;
                int process = remove_process();
                int pr[3];
                int k;
                for(k=0;k<3;k++){
                    pr[k]=process_table[process].allocated_resorce[k];
                    process_table[process].allocated_resorce[k]=0;
                    process_table[process].request_resource[k]=0;
                }
                removed_process++;
                printf("process p%d having instances %d %d %d has been removed from process block\n", process,pr[0],pr[1],pr[2]);
                print_instance();
                goto start;
            }
        }

        if (count_executed_process == number_of_process && flag2 == 0)
        {
            printf("\nAll processes have been executed successfully...\nNo deadLock occur...\n\n");
            break;
        }
    }
}
// function to print allocated instances for each process
void print_allocation()
{
    int i, j;
    for (i = 0; i < number_of_process; i++)
    {
        if (i == 0)
            printf("process allocation :\n\n");
        printf("%s%d ", process_table[i].name, i);
        for (j = 0; j < 3; j++)
        {

            printf("%d ", process_table[i].allocated_resorce[j]);
        }
        printf("\n");
    }
}
// function to print requested instances for each process
void print_request()
{
    int i, j;

    printf("\nprocess request :\n\n");
    for (i = 0; i < number_of_process; i++)
    {
        printf("%s%d ", process_table[i].name, i);
        for (j = 0; j < 3; j++)
        {

            printf("%d ", process_table[i].request_resource[j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    /* code */

    // for (i = 0; i < 5; i++)
    // {
    //     process_table[i].name = (char *)malloc(2 * sizeof(char));
    //     process_table[i].allocated_resorce = malloc(3 * sizeof(int));
    //     process_table[i].request_resource = malloc(3 * sizeof(int));

    //     process_table[i].name = "p";
    //     for (j = 0; j < 3; j++)
    //     {

    //         process_table[i].allocated_resorce[j] = allcoate[i][j];

    //         process_table[i].request_resource[j] = request[i][j];
    //     }
    // }

    // process_table[0].name = (char *)malloc(2 * sizeof(char));
    // process_table[0].name = "p1";
    // process_table[0].allocated_resorce = malloc(3 * sizeof(int));
    // process_table[0].allocated_resorce[0] = 0;
    // process_table[0].allocated_resorce[1] = 1;
    // process_table[0].allocated_resorce[2] = 0;
    // process_table[0].request_resource = malloc(3 * sizeof(int));
    // process_table[0].request_resource[0] = 1;
    // process_table[0].request_resource[1] = 1;
    // process_table[0].request_resource[2] = 0;

    // process_table[1].name = (char *)malloc(2 * sizeof(char));
    // process_table[1].name = "p1";
    // process_table[1].allocated_resorce = malloc(3 * sizeof(int));
    // process_table[1].allocated_resorce[0] = 0;
    // process_table[1].allocated_resorce[1] = 1;
    // process_table[1].allocated_resorce[2] = 0;
    // process_table[1].request_resource = malloc(3 * sizeof(int));
    // process_table[1].request_resource[0] = 1;
    // process_table[1].request_resource[1] = 1;
    // process_table[1].request_resource[2] = 0;

    printf("\nInitial resorces");
    print_instance();
    instance_allocation();
    print_allocation();

    instance_request();
    print_request();
    print_instance();
    execute_process();
    printf("\nAfter execution of processes...");
    printf("\nAvailable resorces");
    print_instance();
    print_allocation();
    print_request();

    return 0;
}
