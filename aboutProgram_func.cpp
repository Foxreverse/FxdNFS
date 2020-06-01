#include "window_about_program.h"



///........HANDLES OF BUTTONS........\\\



void handleOk(GtkWidget* widget, gpointer data){
	gtk_widget_hide((GtkWidget*) data);
}



///........METHODS CLASS "WINDOW_MAIN"........\\\



window_about_program :: window_about_program(){
	w_about_program = GTK_WIDGET(gtk_builder_get_object(builder, "window_aboutProgram"));
}

window_about_program :: ~window_about_program(){}

void window_about_program :: click_to_okey(){
    button_okey = GTK_WIDGET(gtk_builder_get_object(builder, "butOkAbout"));
    g_signal_connect(GTK_BUTTON(button_okey), "clicked", G_CALLBACK(handleOk), w_about_program);
}