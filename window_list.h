#ifndef WINDOW_LIST_H
#define WINDOW_LIST_H

#include "main_header.h"

class window_list
{
public:

      GtkWidget *w_list;

public:

    window_list(){
    	w_list = GTK_WIDGET(gtk_builder_get_object(builder, "window_list"));
   		g_signal_connect(GTK_WIDGET(w_list), "delete_event", G_CALLBACK(gtk_widget_hide), NULL);
    }

    ~window_list(){}

};

#endif