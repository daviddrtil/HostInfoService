/**
 * @file    hinfosvc.h
 * @brief   Definitions and libraries for hinfosvc.c
 * @author  David Drtil <xdrtil03@stud.fit.vutbr.cz>
 * @date    2022-02-20
*/

#ifndef HINFOSVC_H
#define HINFOSVC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include "host_name.h"
#include "cpu_name.h"
#include "cpu_usage.h"

#define MESSAGE_BUFFER_SIZE 2000

// Initial capacity of array
#define ARRAY_INIT_CAP 128

// Cpu usage is in percentage, so maximum number it can reach is 100
// i.e. 3 characters + '%' + '\0' = 5 character
#define PERCENTAGE_STR 5

/**
 * @brief Resizes array to required lenght.
 * @param array_to_resize Array to resize.
 * @param new_size New size of array.
*/
void array_resize(char **array_to_resize, int new_size);

#endif
