#ifndef WINDOW_DOWNLOAD_H
#define WINDOW_DOWNLOAD_H

#include "main_header.h"

extern GtkWidget* entryDownloadText;
extern GtkWidget* dialogDownload;

class window_download
{
public:



///........MAIN WINDOW........///



    GtkWidget* w_download;



///........BUTTONS........///



    GtkWidget* butDownloadDirectory;



///........LISTS(UPLOADS & DOWNLOADS)........///



public:

    window_download();

    ~window_download();

    //void modifier_struct_download();

    void download_directory();

    //void remove_directory();
    
};

#endif