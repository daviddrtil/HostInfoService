/**
 * @file    hinfosvc.c
 * @brief   IPK - project 1
 * @author  David Drtil <xdrtil03@stud.fit.vutbr.cz>
 * @date    2022-02-20
*/

// hinfosvc - Creates a server, that communicates via HTTP protocol and
//            provides information about system.
// Usage: hinfosvc [PORT NUMBER]
// Examples:    hinfosvc 12345 &
//              curl http://localhost:12345/hostname
//              curl http://localhost:12345/cpu-name
//              curl http://localhost:12345/load

#include "hinfosvc.h"

void array_resize(char **array_to_resize, int new_size)
{
    *array_to_resize = (char *)realloc((*array_to_resize), new_size);
    if (array_to_resize == NULL)
    {
        fprintf(stderr, "Reallocating memory in array_resize failed.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Port is missing.\n");
        exit(EXIT_FAILURE);
    }
    uint16_t port_number = (uint16_t)strtol(argv[1], NULL, 10);     // Extracting port number

    int server_fd, new_socket;
    long val_read;
    struct sockaddr_in address;
    int addr_len = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
    {
        fprintf(stderr, "Failed to create a socket.\n");
        exit(EXIT_FAILURE);
    }

    // Enable reusing address
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        fprintf(stderr, "Setsockopt (SO_REUSEADDR) failed.\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_number);
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    // Set the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        fprintf(stderr, "Binding failed.\n");
        exit(EXIT_FAILURE);
    }

    // Socket start to accept connection
    if (listen(server_fd, 10) < 0)
    {
        fprintf(stderr, "Listening failed.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate lenght of each request in advance
    int len_request_hostname = strlen("GET /hostname");
    int len_request_cpuname = strlen("GET /cpu-name");
    int len_request_load = strlen("GET /load");
    while (true)
    {
        // Waiting for new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len)) < 0)
        {
            fprintf(stderr, "Accepting the socket failed.\n");
            exit(EXIT_FAILURE);
        }
        
        char buffer[MESSAGE_BUFFER_SIZE] = {0};   // Buffer to store new message (e.g. "GET /hostname ... ")
        val_read = read(new_socket , buffer, MESSAGE_BUFFER_SIZE);
        if (val_read == -1)
        {
            fprintf(stderr, "Read failed.\n");
            exit(EXIT_FAILURE);
        }

        // Whole message
        char *message = (char *)malloc(ARRAY_INIT_CAP);
        int message_cap = ARRAY_INIT_CAP;
        int message_size = 0;

        // Add header of succesfull message for http server
        char *message_header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n";
        strcpy(message, message_header);
        message_size += strlen(message_header);

        // Write message to server
        if (strncmp(buffer, "GET /hostname", len_request_hostname) == 0)
        {
            char *host_name = get_host_name();
            message_size += strlen(host_name);
            if (message_size >= message_cap)
            {
                message_cap = message_size + 1;		// Increase the capacity
		        array_resize(&message, message_cap);
            }
            strcat(message, host_name);
            message[message_size] = '\0';   // End of message
            
            write(new_socket, message, message_size);

            free(host_name);
        }
        else if (strncmp(buffer, "GET /cpu-name", len_request_cpuname) == 0)
        {
            char *cpu_name = get_cpu_name();
            message_size += strlen(cpu_name);
            if (message_size >= message_cap)
            {
                message_cap = message_size + 1;		// Increase the capacity
		        array_resize(&message, message_cap);
            }
            strcat(message, cpu_name);
            message[message_size] = '\0';   // End of message
            
            write(new_socket, message, message_size);

            free(cpu_name);
        }
        else if (strncmp(buffer, "GET /load", len_request_load) == 0)
        {
            int cpu_usage_value = get_cpu_usage();
            if (cpu_usage_value < 0 || cpu_usage_value > 100)
            {
                fprintf(stderr, "Invalid cpu_usage, out of boundaries.\n");
                exit(EXIT_FAILURE);
            }

            char cpu_usage_str[PERCENTAGE_STR];
            message_size += PERCENTAGE_STR;

            sprintf(cpu_usage_str, "%d%%", cpu_usage_value);
            strcat(message, cpu_usage_str);
            message[message_size] = '\0';   // End of message
            
            write(new_socket, message, strlen(message));
        }
        else
        {
            char *err_message = "400 Bad Request";
            write(new_socket, err_message, strlen(err_message));
        }
        free(message);
        close(new_socket);  // Closing socket
    }
    return 0;
}
