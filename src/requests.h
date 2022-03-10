/**
 * @file    requests.h
 * @brief   Definitions and libraries for requests.c
 * @author  David Drtil <xdrtil03@stud.fit.vutbr.cz>
 * @date    2022-02-20
*/

#ifndef REQUESTS_H
#define REQUESTS_H

#include "hinfosvc.h"

// Number of items in cpu_info_t
#define CPU_INFO_ITEMS 10

#define SLEEP_DURATION_MICROSEC 1000*1000

// Cpu stats
typedef enum
{
    USER,
    NICE,
    SYSTEM,
    IDLE,
    IOWAIT,
    IRQ,
    SOFTIRQ,
    STEAL,
    GUEST,
    GUEST_NICE
} cpu_item;

/**
 * @brief Obtain host name.
 * @return Allocated string (host_name).
*/
char *get_host_name();

/**
 * @brief Obtain cpu name.
 * @return Allocated string (cpu_name).
*/
char *get_cpu_name();

/**
 * @brief Extract cpu informations from /proc/stat.
 * @param cpu_info Reference to array of cpu stats.
*/
void extract_cpu_info(uint64_t **cpu_info);

/**
 * @brief Obtain cpu usage / cpu load.
 * @return Cpu usage in percentage.
*/
int get_cpu_usage();

#endif

/** End of file requests.h **/