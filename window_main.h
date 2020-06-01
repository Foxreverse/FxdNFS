#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include "main_header.h"
#include "window_reference.h"
#include "window_about_program.h"
#include "window_list.h"
#include "window_upload.h"
#include "window_download.h"



///....HANDLES & PROCEDURS....\\\



void handleUpload(GtkWidget* widget, gpointer data);
void handleDownload(GtkWidget* widget, gpointer data);
void handleReference(GtkWidget* widget, gpointer data);
void handleAboutProgram(GtkWidget* widget, gpointer data);
void handleUserlist(GtkWidget* widget, gpointer data);



///........COMBINED MODIFICATIONS........\\\



void handleUploadDirectory(GtkWidget* widget, gpointer data);
void handleRemoveDirectory(GtkWidget* widget, gpointer data);

void handleDownloadDirectory(GtkWidget* widget, gpointer data);

extern window_upload WINUPLOAD;
extern window_download WINDOWNLOAD;

class window_main
{
public:



///........MAIN WINDOW........\\\



    GtkWidget* w_main; 



///........BUTTONS........\\\



    GtkWidget* butUpload;
    GtkWidget* butDownload;
    GtkWidget* butRemove;
    GtkWidget* referenceChoose;
    GtkWidget* aboutProgramChoose;
    GtkWidget* butCheck;

public:

    window_main();

    ~window_main();

    void upload();
    
	void remove_from_list();

	void download();
	
	void show_reference();

	void show_about_program();
	
	void show_userlist();

};

#endif