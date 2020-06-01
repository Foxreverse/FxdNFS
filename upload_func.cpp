#include "window_upload.h"



///........DATA IMPLEMENTATION(window_upload.h)........\\\



struct mainObjectsForm{
        GtkWidget    *treeViewUploads = gtk_widget_new(G_TYPE_OBJECT, NULL, NULL, NULL, NULL);
        GtkListStore   *listStoreUploads = gtk_list_store_new(0, 0, 0, 0);
    }Objects;

GtkWidget* entryText = gtk_widget_new(G_TYPE_OBJECT, NULL, NULL, NULL, NULL);
GtkWidget* dialog = gtk_widget_new(G_TYPE_OBJECT, NULL, NULL, NULL, NULL);
GtkTreeIter iter;



///..........PROCEDURS..........\\\



static void remove_row (GtkTreeRowReference *ref, GtkTreeModel *model){
    GtkTreeIter iter;
    GtkTreePath *path;
    path = gtk_tree_row_reference_get_path (ref);
    gtk_tree_model_get_iter (model, &iter, path);
    gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
}



///........METHODS CLASS "WINDOW_MAIN"........\\\



window_upload :: window_upload(){}

window_upload :: ~window_upload(){}

void window_upload :: modifier_struct(){
    Objects.treeViewUploads = GTK_WIDGET(gtk_builder_get_object(builder, "treeViewUploads"));
    Objects.listStoreUploads = GTK_LIST_STORE(gtk_builder_get_object(builder, "listStoreUploads"));   
    dialog = GTK_WIDGET(gtk_builder_get_object(builder, "chooseUpload"));
}

void window_upload :: upload_directory(){
    Objects.treeViewUploads = GTK_WIDGET(gtk_builder_get_object(builder, "treeViewUploads"));
    Objects.listStoreUploads = GTK_LIST_STORE(gtk_builder_get_object(builder, "listStoreUploads"));   
    dialog = GTK_WIDGET(gtk_builder_get_object(builder, "chooseUpload"));
    gtk_list_store_append(Objects.listStoreUploads, &iter);
    gtk_list_store_set(GTK_LIST_STORE(Objects.listStoreUploads), &iter, 0, (char*)gtk_entry_get_text((GtkEntry* ) entryText), -1);
    gtk_entry_set_text((GtkEntry*)entryText, "");
    gtk_widget_hide(w_upload);
    cout << "UPLOAD" << endl;
    g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
}

void window_upload :: remove_directory(){
    cout << "Delete is!" << endl;
    GtkTreeSelection *selection;
    GtkTreeRowReference *ref;
    GtkTreeModel *model;
    GList *rows, *ptr, *references = NULL;
    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW(Objects.treeViewUploads));
    model = gtk_tree_view_get_model (GTK_TREE_VIEW(Objects.treeViewUploads));
    rows = gtk_tree_selection_get_selected_rows (selection, &model);

    ptr = rows;
    while (ptr != NULL)
    {
        ref = gtk_tree_row_reference_new (model, (GtkTreePath*) ptr->data);
        references = g_list_prepend (references, gtk_tree_row_reference_copy (ref));
        gtk_tree_row_reference_free (ref);
        ptr = ptr->next;
    }
    
    g_list_foreach ( references, (GFunc) remove_row, model );
    g_list_foreach ( references, (GFunc) gtk_tree_row_reference_free, NULL );
    g_list_foreach ( rows, (GFunc) gtk_tree_path_free, NULL );
    g_list_free ( references );
    g_list_free ( rows );
}