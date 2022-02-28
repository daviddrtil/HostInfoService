/**
 * @file    host_name.h
 * @brief   Definitions and libraries for host_name.c
 * @author  David Drtil <xdrtil03@stud.fit.vutbr.cz>
 * @date    2022-02-20
*/

#ifndef HOST_NAME_H
#define HOST_NAME_H

#include "hinfosvc.h"

/**
 * @brief Obtain host name.
 * @return Allocated string (host_name).
*/
char *get_host_name();

#endif
