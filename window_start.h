#ifndef WINDOW_START_H
#define WINDOW_START_H

#include "main_header.h"
#include "window_sign.h"
#include "window_signup.h"

void create_window_sign();

void create_window_signup();

void handle_sign_in(GtkWidget *widget, gpointer user_data);

void handle_sign_up(GtkWidget *widget, gpointer user_data);

class window_start
{
public:

      GtkWidget *w_message;
      GtkWidget *button_exit;
      GtkWidget *button_sign_in;
      GtkWidget *button_sign_up;

public:

    window_start();

    ~window_start();
    
    void exit_from_the_program();

    void message_sign_in();

    void message_sign_up();

};

#endif