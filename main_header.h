#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include <gtk/gtk.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <experimental/filesystem>
#include <unistd.h>
#define MAXLINE 512

using namespace std;
namespace fs = std::experimental::filesystem;

extern GtkBuilder* builder;
extern GtkWidget* w_connect;

#endif