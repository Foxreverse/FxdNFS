#include "window_sign.h"



///........HANDLES OF BUTTONS........\\\



void handle_sign(GtkWidget *widget, gpointer user_data){
    gtk_widget_destroy((GtkWidget*) user_data);
    gtk_widget_show(w_connect);
}




///........METHODS CLASS "WINDOW_MAIN"........\\\


window_sign :: window_sign(){
    w_sign = GTK_WIDGET(gtk_builder_get_object(builder, "window_sign"));
}

window_sign :: ~window_sign(){}

void window_sign :: exit_from_the_program(){
    button_exit = GTK_WIDGET(gtk_builder_get_object(builder, "but_exit"));
    g_signal_connect(GTK_BUTTON(button_exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
}

void window_sign :: clicked_to_sign(){
    button_sign = GTK_WIDGET(gtk_builder_get_object(builder, "but_sign"));
    g_signal_connect(GTK_BUTTON(button_sign), "clicked", G_CALLBACK(handle_sign), w_sign);
}