#include "window_start.h"




///........PROCEDURES........\\\




void create_window_sign()
{
    window_sign WINSIGN;
    WINSIGN.exit_from_the_program();
    WINSIGN.clicked_to_sign();
    gtk_widget_show(WINSIGN.w_sign);
}

void create_window_signup()
{
    window_signup WINSIGNUP;
    WINSIGNUP.exit_from_the_program();
    WINSIGNUP.clicked_to_create();
    gtk_widget_show(WINSIGNUP.w_signup);
}





///........HANDLES OF BUTTONS........\\\





void handle_sign_in(GtkWidget *widget, gpointer user_data)
{
    gtk_widget_destroy((GtkWidget*) user_data);
    create_window_sign();
}

void handle_sign_up(GtkWidget *widget, gpointer user_data)
{
    gtk_widget_destroy((GtkWidget*) user_data);
    create_window_signup();
}




///........METHODS CLASS "WINDOW_MAIN"........\\\




window_start :: window_start(){
    w_message = GTK_WIDGET(gtk_builder_get_object(builder, "window_message"));
}

window_start :: ~window_start(){}

void window_start :: exit_from_the_program(){
    button_exit = GTK_WIDGET(gtk_builder_get_object(builder, "mes_but1"));
    g_signal_connect(GTK_BUTTON(button_exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
}

void window_start :: message_sign_in(){
    button_sign_in = GTK_WIDGET(gtk_builder_get_object(builder, "mes_but2"));
    g_signal_connect(GTK_BUTTON(button_sign_in), "clicked", G_CALLBACK(handle_sign_in), w_message);
}

void window_start :: message_sign_up(){
    button_sign_up = GTK_WIDGET(gtk_builder_get_object(builder, "mes_but3"));
    g_signal_connect(GTK_BUTTON(button_sign_up), "clicked", G_CALLBACK(handle_sign_up), w_message);
}
