#ifndef WINDOW_SIGN_H
#define WINDOW_SIGN_H

#include "main_header.h"

void handle_sign(GtkWidget *widget, gpointer user_data);

class window_sign
{
public:

    GtkWidget *w_sign;
    GtkWidget *button_exit;
    GtkWidget *button_sign;

public:

    window_sign();

    ~window_sign();

    void exit_from_the_program();
        
    void clicked_to_sign();

};

#endif