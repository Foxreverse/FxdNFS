#include "window_download.h"



///........DATA IMPLEMENTATION(window_upload.h)........\\\



GtkWidget* entryDownloadText = gtk_widget_new(G_TYPE_OBJECT, NULL, NULL, NULL, NULL);
GtkWidget* dialogDownload = gtk_widget_new(G_TYPE_OBJECT, NULL, NULL, NULL, NULL);


///..........PROCEDURS..........\\\



///........METHODS CLASS "WINDOW_MAIN"........\\\



window_download :: window_download(){}

window_download :: ~window_download(){}

void window_download :: download_directory(){
    dialogDownload = GTK_WIDGET(gtk_builder_get_object(builder, "chooseDownload"));
    gtk_entry_set_text((GtkEntry*)entryDownloadText, "");
    gtk_widget_hide(w_download);
    g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialogDownload)));
}
