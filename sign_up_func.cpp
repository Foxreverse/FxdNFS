#include "window_signup.h"



///........HANDLES OF BUTTONS........\\\



void handle_signup(GtkWidget *widget, gpointer user_data){
    gtk_widget_destroy((GtkWidget*) user_data);
    gtk_widget_show(w_connect);
}




///........METHODS CLASS "WINDOW_MAIN"........\\\




window_signup :: window_signup(){
    w_signup = GTK_WIDGET(gtk_builder_get_object(builder, "window_signup"));
}

window_signup :: ~window_signup(){}

void window_signup :: exit_from_the_program(){
    button_exit = GTK_WIDGET(gtk_builder_get_object(builder, "but_exit_1"));
    g_signal_connect(GTK_BUTTON(button_exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
}

void window_signup :: clicked_to_create(){
    button_create = GTK_WIDGET(gtk_builder_get_object(builder, "but_create"));
    g_signal_connect(GTK_BUTTON(button_create), "clicked", G_CALLBACK(handle_signup), w_signup);
}