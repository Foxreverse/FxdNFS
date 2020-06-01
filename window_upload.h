#ifndef WINDOW_UPLOAD_H
#define WINDOW_UPLOAD_H

#include "main_header.h"

extern GtkWidget* entryText;
extern struct mainObjectsForm Objects;
extern GtkTreeIter iter;
extern GtkWidget *dialog;

static void remove_row (GtkTreeRowReference *ref, GtkTreeModel *model);

class window_upload
{
public:



///........MAIN WINDOW........///



    GtkWidget* w_upload;



///........BUTTONS........///



    GtkWidget* butUploadDirectory;



///........LISTS(UPLOADS & DOWNLOADS)........///



public:

    window_upload();

    ~window_upload();

    void modifier_struct();

    void upload_directory();

    void remove_directory();
    
};

#endif