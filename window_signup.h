#ifndef WINDOW_SIGN_UP_H
#define WINDOW_SIGN_UP_H

#include "main_header.h"

void handle_create(GtkWidget *widget, gpointer user_data);

class window_signup
{
  public:

      GtkWidget *w_signup;
      GtkWidget *button_exit;
      GtkWidget *button_create;

  public:

      window_signup();

      ~window_signup();

      void exit_from_the_program();

      void clicked_to_create();

};
#endif