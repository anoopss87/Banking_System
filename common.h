/*
 * Advanced Operating Systems - Spring 2016 
 * Programming Project #1
 * 
 * common.h - Common includes and Structures
 * @author - Anoop S
*/

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <queue>
#include <map>
#include <string>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>
using namespace std;

#define NUM_OF_SERVERS 3

struct msgPkt{
    char cmd[12];
    char fname[16];
    char data[1024];
    int master_server;    
    int optParam;
    char context[2];
};

extern map<string, string> serverList;
#endif
