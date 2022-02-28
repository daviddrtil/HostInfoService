/**
 * @file    cpu_usage.h
 * @brief   Definitions and libraries for cpu_usage.c
 * @author  David Drtil <xdrtil03@stud.fit.vutbr.cz>
 * @date    2022-02-20
*/

#ifndef CPU_USAGE_H
#define CPU_USAGE_H

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
