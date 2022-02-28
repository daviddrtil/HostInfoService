/**
 * @file    host_name.c
 * @brief   Server request hostname
 * @author  David Drtil <xdrtil03@stud.fit.vutbr.cz>
 * @date    2022-02-20
*/

#include "host_name.h"

char *get_host_name()
{
    FILE *ptr_file;
    ptr_file = popen("cat /proc/sys/kernel/hostname", "r");
    if (ptr_file == NULL)
    {
        fprintf(stderr, "Peopen failed.\n");
        exit(EXIT_FAILURE);
    }

    char *host_name = (char *)malloc(ARRAY_INIT_CAP);
    if (host_name == NULL)
    {
        fprintf(stderr, "Allocation of host_name string failed.\n");
        exit(EXIT_FAILURE);
    }
    
    int idx = 0;
    int c;
    while (isalnum(c = fgetc(ptr_file)) || c == '-' || c == '_')    // Load valid characters
    {
        host_name[idx] = c;
        idx++;
    }
    host_name[idx] = '\0';

    pclose(ptr_file);
    return host_name;
}
