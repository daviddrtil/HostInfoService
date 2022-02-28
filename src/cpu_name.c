/**
 * @file    cpu_name.c
 * @brief   Server request cpu-name
 * @author  David Drtil <xdrtil03@stud.fit.vutbr.cz>
 * @date    2022-02-20
*/

#include "cpu_name.h"

char *get_cpu_name()
{
    // Get full cpu name
    FILE *command_result;
    command_result = popen("cat /proc/cpuinfo | grep \"model name\" | cut -c 14-", "r");
    if (command_result == NULL)
    {
        fprintf(stderr, "Peopen failed.\n");
        exit(EXIT_FAILURE);
    }

    int c;
    int idx = 0;
    char *cpu_name = (char *)malloc(ARRAY_INIT_CAP);
    if (cpu_name == NULL)
    {
        fprintf(stderr, "Allocation of cpu_name string failed.\n");
        exit(EXIT_FAILURE);
    }

    while ((c = fgetc(command_result)) != '\n')    // Load valid characters
    {
        cpu_name[idx] = c;
        idx++;
    }
    cpu_name[idx] = '\0';

    pclose(command_result);
    return cpu_name;
}