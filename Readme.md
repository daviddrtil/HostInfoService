# IPK - project 1

Creates a server, that communicates via HTTP protocol and provides information about system.

The server listen on specific port and via url send answers.

Communication with the server is possible with web browser and tools like wget, curl.

## Getting started

Via makefile compile and build project. 

Write command "make", which creates executable file "hinfosvc".

The server is executable with argument indicating port number.

It's able to process 3 types of requests:
1) Obtain domain name - the network name of computer, including the domain
2) Obtain full cpu name
3) Obtain current cpu load / cpu usage

The server is possible to shut down by 'CTRL + C'.

### Prerequisites
1) Compiler for language c: gcc
2) Program: make

## Usage

hinfosvc [PORT NUMBER]

$ First example
./hinfosvc 12345 & curl http://localhost:12345/hostname

$ Second example
./hinfosvc 65026 & curl http://localhost:12345/cpu-name

$ Third example
./hinfosvc 98765 & curl http://localhost:12345/load


## Author
David Drtil, <xdrtil03@stud.fit.vutbr.cz>

