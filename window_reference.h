#ifndef WINDOW_REFERENCE_H
#define WINDOW_REFERENCE_H

#include "main_header.h"

void handleOkey(GtkWidget* widget, gpointer data);

class window_reference {

public:

	GtkWidget *w_reference;
	GtkWidget *button_ok;

	public:

	window_reference();

	~window_reference();

   	void click_to_ok();

};

#endif