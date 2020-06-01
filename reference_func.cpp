#include "window_reference.h"



///........HANDLES OF BUTTONS........\\\



void handleOkey(GtkWidget* widget, gpointer data){
	cout<<"LOL"<<endl;
	gtk_widget_hide_on_delete((GtkWidget*) data);
	return;
}



///........METHODS CLASS "WINDOW_MAIN"........\\\



window_reference :: window_reference(){
	w_reference = GTK_WIDGET(gtk_builder_get_object(builder, "window_reference"));
}

window_reference :: ~window_reference(){}

void window_reference :: click_to_ok(){
    button_ok = GTK_WIDGET(gtk_builder_get_object(builder, "buttonOk"));
    g_signal_connect(G_OBJECT(button_ok), "clicked", G_CALLBACK(handleOkey), w_reference);
}