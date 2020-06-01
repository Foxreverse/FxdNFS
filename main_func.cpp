#include "window_main.h"



window_upload WINUPLOAD;
window_download WINDOWNLOAD;



///........HANDLES OF BUTTONS........\\\



void handleUpload(GtkWidget* widget, gpointer data){
    gtk_widget_show(WINUPLOAD.w_upload);
}

void handleDownload(GtkWidget* widget, gpointer data){
    gtk_widget_show(WINDOWNLOAD.w_download);
}

void handleReference(GtkWidget* widget, gpointer data){
    window_reference WINREFERENCE;
    WINREFERENCE.click_to_ok();
    gtk_widget_show(WINREFERENCE.w_reference);
    cout << "REFERENCE" << endl;
}

void handleAboutProgram(GtkWidget* widget, gpointer data){
    window_about_program WINABOUTPROGRAM;
    WINABOUTPROGRAM.click_to_okey();
    gtk_widget_show(WINABOUTPROGRAM.w_about_program);
    cout << "ABOUT" << endl;
}

void handleUserlist(GtkWidget* widget, gpointer data){
    cout << "USERLIST" << endl;
    window_list WINLIST;
    gtk_widget_show(WINLIST.w_list);
}

void handleUploadDirectory(GtkWidget* widget, gpointer data){
    WINUPLOAD.upload_directory();
}

void handleRemoveDirectory(GtkWidget* widget, gpointer data){
    WINUPLOAD.remove_directory();
}

void handleDownloadDirectory(GtkWidget* widget, gpointer data){
    WINDOWNLOAD.download_directory();
}



///........METHODS CLASS "WINDOW_MAIN"........\\\



window_main :: window_main() {
    w_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    g_signal_connect(G_OBJECT(w_main), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    WINUPLOAD.w_upload = GTK_WIDGET(gtk_builder_get_object(builder, "window_upload"));
    WINDOWNLOAD.w_download = GTK_WIDGET(gtk_builder_get_object(builder, "window_download"));

    entryText = GTK_WIDGET(gtk_builder_get_object(builder, "entryDirectoryName"));
    entryDownloadText = GTK_WIDGET(gtk_builder_get_object(builder, "entryDownloadDirectoryName"));
    
    WINUPLOAD.modifier_struct();
    
    WINUPLOAD.butUploadDirectory = GTK_WIDGET(gtk_builder_get_object(builder, "butUploadDirectory"));
    g_signal_connect(GTK_WIDGET(WINUPLOAD.w_upload), "delete_event", G_CALLBACK(gtk_widget_hide), NULL);

    WINDOWNLOAD.butDownloadDirectory = GTK_WIDGET(gtk_builder_get_object(builder, "butDownloadDirectory"));
    g_signal_connect(GTK_WIDGET(WINDOWNLOAD.w_download), "delete_event", G_CALLBACK(gtk_widget_hide), NULL);
}

window_main :: ~window_main(){}

void window_main :: upload(){
    butUpload = GTK_WIDGET(gtk_builder_get_object(builder, "butUpload"));
    g_signal_connect(GTK_BUTTON(butUpload), "clicked", G_CALLBACK(handleUpload), NULL);

    WINUPLOAD.butUploadDirectory = GTK_WIDGET(gtk_builder_get_object(builder, "butUploadDirectory"));
    g_signal_connect(GTK_BUTTON(WINUPLOAD.butUploadDirectory), "clicked", G_CALLBACK(handleUploadDirectory), NULL);
}

void window_main :: remove_from_list(){
    butRemove = GTK_WIDGET(gtk_builder_get_object(builder, "butRemove"));
    g_signal_connect(GTK_BUTTON(butRemove), "clicked", G_CALLBACK(handleRemoveDirectory), NULL);
}

void window_main :: download(){
    butDownload = GTK_WIDGET(gtk_builder_get_object(builder, "butDownload"));
    g_signal_connect(GTK_BUTTON(butDownload), "clicked", G_CALLBACK(handleDownload), NULL);

    WINDOWNLOAD.butDownloadDirectory = GTK_WIDGET(gtk_builder_get_object(builder, "butDownloadDirectory"));
    g_signal_connect(GTK_BUTTON(WINDOWNLOAD.butDownloadDirectory), "clicked", G_CALLBACK(handleDownloadDirectory), NULL);    
}

void window_main :: show_reference(){
    referenceChoose = GTK_WIDGET(gtk_builder_get_object(builder, "referenceChoose"));
    g_signal_connect(GTK_MENU_ITEM(referenceChoose), "activate", G_CALLBACK(handleReference), NULL);
}

void window_main :: show_about_program(){
    aboutProgramChoose = GTK_WIDGET(gtk_builder_get_object(builder, "aboutProgramChoose"));
    g_signal_connect(GTK_MENU_ITEM(aboutProgramChoose), "activate", G_CALLBACK(handleAboutProgram), NULL);
}

void window_main :: show_userlist(){
    butCheck = GTK_WIDGET(gtk_builder_get_object(builder, "butCheck"));
    g_signal_connect(GTK_BUTTON(butCheck), "clicked", G_CALLBACK(handleUserlist), NULL);
}
