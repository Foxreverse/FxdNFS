#ifndef WINDOW_ABOUT_PROGRAM_H
#define WINDOW_ABOUT_PROGRAM_H

#include "main_header.h"

void handleOk(GtkWidget* widget, gpointer data);

class window_about_program {

public:

	GtkWidget *w_about_program;
	GtkWidget *button_okey;

	public:

	window_about_program();

	~window_about_program();

   	void click_to_okey();

};

#endif