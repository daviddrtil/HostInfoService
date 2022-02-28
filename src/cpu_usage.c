/**
 * @file    cpu_usage.c
 * @brief   Server request load (cpu usage) 
 * @author  David Drtil <xdrtil03@stud.fit.vutbr.cz>
 * @date    2022-02-20
*/

#include "cpu_usage.h"

void extract_cpu_info(uint64_t **cpu_info)
{
    FILE *command_result;
    command_result = popen("cat /proc/stat | head -n 1", "r");
    if (command_result == NULL)
    {
        fprintf(stderr, "Peopen failed.\n");
        exit(EXIT_FAILURE);
    }
    
    // Skip all characters until first number
    int c;
    while (!isdigit(c = fgetc(command_result)));

    // Allocating cpu_info array
    *cpu_info = (uint64_t *)malloc(sizeof(uint64_t) * CPU_INFO_ITEMS);
    if (*cpu_info == NULL)
    {
        fprintf(stderr, "Allocation of cpu_info array failed.\n");
        exit(EXIT_FAILURE);
    }

    char tmp_str[sizeof(uint64_t)+1];   // Size is number of bytes in uint64 + '\0'
    tmp_str[0] = c; // Store first digit of number (was already loaded from previous step)
    int idx = 1;
    for (int i = 0; i < CPU_INFO_ITEMS; i++)
    {
        // Load all cpu information
        while (isdigit(c = fgetc(command_result)))
        {
            tmp_str[idx++] = c;
        }
        tmp_str[idx] = '\0';
        (*cpu_info)[i] = strtol(tmp_str, NULL, 10);
        idx = 0;    // Reset counter for new item (new number)
    }
    
    pclose(command_result); // Closing stream
}

int get_cpu_usage()
{
    // Load cpu stats
    uint64_t *prev_cpu_info = NULL;
    extract_cpu_info(&prev_cpu_info);

    usleep(SLEEP_DURATION_MICROSEC);  // Wait a one second

    uint64_t *cur_cpu_info = NULL;
    extract_cpu_info(&cur_cpu_info);

    // Calculation of cpu usage
    uint64_t prev_idle = prev_cpu_info[IDLE] + prev_cpu_info[IOWAIT];
    uint64_t cur_idle = cur_cpu_info[IDLE] + cur_cpu_info[IOWAIT];

    uint64_t prev_non_idle = prev_cpu_info[USER] + prev_cpu_info[NICE] + prev_cpu_info[SYSTEM];
    prev_non_idle += prev_cpu_info[IRQ] + prev_cpu_info[SOFTIRQ] + prev_cpu_info[STEAL];
    uint64_t cur_non_idle = cur_cpu_info[USER] + cur_cpu_info[NICE] + cur_cpu_info[SYSTEM];
    cur_non_idle += cur_cpu_info[IRQ] + cur_cpu_info[SOFTIRQ] + cur_cpu_info[STEAL];

    uint64_t prev_total = prev_idle + prev_non_idle;
    uint64_t cur_total = cur_idle + cur_non_idle;

    // Differentiate actual value minus previous one
    uint64_t total_dif = cur_total - prev_total;
    uint64_t idle_dif = cur_idle - prev_idle;

    // Result
    double cpu_usage_percetage = ((total_dif - idle_dif) * 100.) / total_dif;

    free(prev_cpu_info);
    free(cur_cpu_info);

    // Return result rounded to whole number
    return (int)(cpu_usage_percetage + 0.5);
}
