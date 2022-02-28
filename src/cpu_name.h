/**
 * @file    cpu_name.h
 * @brief   Definitions and libraries for cpu_name.c
 * @author  David Drtil <xdrtil03@stud.fit.vutbr.cz>
 * @date    2022-02-20
*/

#ifndef CPU_NAME_H
#define CPU_NAME_H

#include "hinfosvc.h"

/**
 * @brief Obtain cpu name.
 * @return Allocated string (cpu_name).
*/
char *get_cpu_name();

#endif
