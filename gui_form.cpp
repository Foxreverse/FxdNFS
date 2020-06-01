// g++ gui_form.cpp -o `pkg-config --cflags --libs gtk+-3.0` -rdynamic

#include "main_header.h"
#include "window_main.h"
#include "window_start.h"

GtkBuilder* builder = gtk_builder_new();
GtkWidget* w_connect = gtk_widget_new(G_TYPE_OBJECT, NULL, NULL, NULL, NULL);

extern "C" void connect_to_server(GtkButton *butConnect, gpointer user_data);

int sockfd;
struct sockaddr_in servaddr;
char sendline[MAXLINE], recvline[MAXLINE];

int create_socket(int,char *);

int main(int argc, char **argv){
    
    gtk_init(&argc, &argv);

    gtk_builder_add_from_file (builder, "part_1.glade", NULL);
    
    w_connect = GTK_WIDGET(gtk_builder_get_object(builder, "window_connect"));
    gtk_builder_connect_signals (builder, NULL);    
    
    window_main WINMAIN;
    window_start WINSTART;

    WINSTART.exit_from_the_program();
    WINSTART.message_sign_in();
    WINSTART.message_sign_up();

    WINMAIN.upload();
    WINMAIN.download();
    WINMAIN.remove_from_list();
    WINMAIN.show_reference();
    WINMAIN.show_about_program();
    WINMAIN.show_userlist();                    

    gtk_widget_show(WINMAIN.w_main);
    gtk_widget_show(WINSTART.w_message);
    gtk_main();

    return 0;
}

int create_socket(int port,char *addr)
{
     int sockfd;
     struct sockaddr_in servaddr;

     if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
        cerr<<"Problem in creating the socket"<<endl;
        exit(2);
     }

     memset(&servaddr, 0, sizeof(servaddr));
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr= inet_addr("127.0.0.1");
     cout << "CLIENT_SOCK" << port << endl;
     servaddr.sin_port =  htons(port);

     socklen_t clen = sizeof(servaddr);
     if (connect(sockfd, (struct sockaddr *) &servaddr, clen)<0) {
        cerr<<"Problem in creating data channel"<<endl;
        exit(3);
     }

return(sockfd);
}

void connect_to_server(GtkButton *butConnect, gpointer data){
    cerr << "CONNECT" << endl;
    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
        cerr<<"Problem in creating the socket"<<endl;
        exit(2);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= inet_addr("127.0.0.1");
    servaddr.sin_port =  htons(3330);

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
        cerr<<"Problem in connecting to the server"<<endl;
        exit(3);
    }

    cerr << "SUCCESFULLY CONNECT!" << endl;
    gtk_widget_hide(w_connect);
}