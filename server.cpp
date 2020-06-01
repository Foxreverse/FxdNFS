#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <dirent.h>
#include <exception>
#include <experimental/filesystem>

using namespace std;
namespace fs = std::experimental::filesystem;

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif
#define MAXLINE 512
#define LISTENQ 8
#define MAX_COUNT 8

int global_port = 0;
int data_port = 1024;
int listenfdS, connfd, n;
pid_t childpid;
socklen_t clilen;
char buf[MAXLINE];
struct sockaddr_in cliaddr, servaddr;
int mas_thread[MAX_COUNT];
int COUNT_THREAD = 0;
pthread_t mas_id[MAX_COUNT];

int create_socket(int port)
{
	int listenfd;
	struct sockaddr_in dataservaddr;
	if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
		cerr<<"Problem in creating the data socket"<<endl;
		exit(2);
	}

	dataservaddr.sin_family = AF_INET;
	dataservaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	dataservaddr.sin_port = htons(port);

	socklen_t clen = sizeof(dataservaddr);

	cout << "CREATESOCKET = " << port << endl;
	if ((bind (listenfd, (struct sockaddr *) &dataservaddr, clen)) < 0) {
		cerr<<"Problem in binding the data socket"<<endl;
		exit(2);
	}

 	listen (listenfd, 1);

	return(listenfd);
}

int accept_conn(int sock)
{
	int dataconnfd;
	socklen_t dataclilen;
	struct sockaddr_in datacliaddr;

	dataclilen = sizeof(datacliaddr);	
  	
  	if ((dataconnfd = accept (sock, (struct sockaddr *) &datacliaddr, &dataclilen)) <0) {
		cerr<<"Problem in accepting the data socket"<<endl;
	exit(2);
	}

	return(dataconnfd);
}

void * client_thread(void * arg)
{
	int newSocket = *((int *)arg);
  	cout<<"Child thread created!"<<endl;
 
  	while ( (n = recv(newSocket, buf, MAXLINE,0)) > 0)  {
  		cout<<"String received from client: "<<buf;
   		char *token,*dummy;
   		dummy=buf;
   		token=strtok(dummy," ");
   		cout << token;

   		if (strcmp("quit\n",buf)==0)  {   /////////   QUIT
   			cout<<"The client has quit\n";
   			close(listenfdS);
   		}

   		else if (strcmp("cd",token)==0)  {   /////////   CD
			token=strtok(NULL," \n");
			cout<<"Path given is: "<<token<<endl;
				
			if(chdir(token)<0){
				send(connfd,"0",MAXLINE,0);
			}

			else{
				send(connfd,"1",MAXLINE,0);
			}
   		}

	    else if (strcmp("put",token)==0)  {   /////////   PUT
			char port[MAXLINE];
			char buffer[MAXLINE];
			char char_num_blks[MAXLINE];
			char char_num_last_blk[MAXLINE];
			char check[MAXLINE];
			char namefile[MAXLINE];
			
			char buf_pop[60], buf_push[60];
			getcwd(buf_pop, sizeof(buf_pop));
		    getcwd(buf_push, sizeof(buf_push));

			int datasock, num_blks, num_last_blk, i;
			
			FILE *fp;
			
			token=strtok(NULL," \n");
			
			cout<<"Directory name given is: "<<token<<endl;
            
            mkdir(token, 0777);
			
			strcat(strcat(buf_pop, "/"), token);
			chdir(buf_pop);

			data_port=data_port+1;
			if(data_port==global_port){
				data_port=data_port+1;
			}
				
			sprintf(port,"%d",data_port);
			
			datasock=create_socket(data_port);				
			
			send(connfd, port,MAXLINE,0);					
			
			datasock=accept_conn(datasock);					

			while(true)
			{
				recv(connfd,check,MAXLINE,0);
				if(strcmp("1",check)==0){
					recv(connfd, namefile, MAXLINE, 0);
					if((fp=fopen(namefile,"wb"))==NULL){
						cout<<"Error in creating file\n";
						break;
					}
					else
					{
						recv(connfd, char_num_blks, MAXLINE,0);
						num_blks=atoi(char_num_blks);
							
						for(i= 0; i < num_blks; i++) { 
							recv(datasock, buffer, MAXLINE,0);
							fwrite(buffer,1,MAXLINE,fp);
						}
				
						recv(connfd, char_num_last_blk, MAXLINE,0);
						num_last_blk=atoi(char_num_last_blk);
						
						if (num_last_blk > 0) { 
							recv(datasock, buffer, MAXLINE,0);
							fwrite(buffer,1,num_last_blk,fp);
						}
						fclose(fp);
						cout<<"File download done.\n";
					}
				}
				else {
					cout << "ErrorFileTo" << endl;
					break;
				}
   			}
   			chdir(buf_push);
   		}

  		if (strcmp("get",token)==0)  {   /////////   GET

			char port[MAXLINE];
			char buffer[MAXLINE];
			char char_num_blks[MAXLINE];
			char char_num_last_blk[MAXLINE];
			
			char buf_pop[60], buf_push[60];
			getcwd(buf_pop, sizeof(buf_pop));
			getcwd(buf_push, sizeof(buf_push));

			int datasock, lSize, num_blks, num_last_blk, i;
			
			FILE *fp;
	
			token=strtok(NULL," \n");
			
			cout<<"Filename given is: "<<token<<endl;
			
			data_port=data_port+1;
			
			if(data_port==global_port){
				data_port=data_port+1;
			}
			
			sprintf(port,"%d",data_port);
			
			datasock=create_socket(data_port);			
			
			send(connfd, port,MAXLINE,0);				
			
			datasock=accept_conn(datasock);					
			
			if(fs::is_directory(token))
			{
				strcat(strcat(buf_pop, "/"), token);
				chdir(buf_pop);

				for(fs::recursive_directory_iterator i (buf_pop), end; i!=end; i++)		
				{
					if ((fp=fopen(i->path().filename().c_str(),"rb"))!=NULL)
					{
						send(connfd, "1",MAXLINE,0);
						send(connfd, i->path().filename().c_str(), MAXLINE, 0);

						cout << i->path().filename().c_str() << endl;

						fseek (fp , 0 , SEEK_END);
						lSize = ftell (fp);
						rewind (fp);
						num_blks = lSize/MAXLINE;
						num_last_blk = lSize%MAXLINE; 
						sprintf(char_num_blks,"%d",num_blks);
						send(connfd, char_num_blks, MAXLINE, 0);
						
						for(int i = 0; i < num_blks; i++) { 
							fread (buffer,1,MAXLINE,fp);
							send(datasock, buffer, MAXLINE, 0);
						}
				
						sprintf(char_num_last_blk,"%d",num_last_blk);
						send(connfd, char_num_last_blk, MAXLINE, 0);
					
						if (num_last_blk > 0) { 
							fread (buffer,1,num_last_blk,fp);
							send(datasock, buffer, MAXLINE, 0);
						}
						fclose(fp);
						cout<<"File upload done.\n";	
					}
					
					else{
						send(connfd,"0",MAXLINE,0);
						cout << "ErrorOpen" << endl;
					}	
   				}
   			send(connfd, "0", MAXLINE, 0);
   			chdir(buf_push);
   			}
   			else
   				cout << "Not DIrectory" << endl;
   		}
   	}
if (n < 0)
   	cout<<"Read error"<<endl;
  exit(0);
}

int main (int argc, char **argv)
{
   	if (argc !=2) {					
  		cerr<<"Usage: ./a.out <port number>"<<endl;
  		exit(1);
 	}

 	if ((listenfdS = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  		cerr<<"Problem in creating the socket"<<endl;
  		exit(2);
 	}

	servaddr.sin_family = AF_INET;
 	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 	if(atoi(argv[1])<=1024){
		cerr<<"Port number must be greater than 1024"<<endl;
		exit(2);
 	}
 	global_port = atoi(argv[1]);
 	servaddr.sin_port = htons(global_port);

	if(bind (listenfdS, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
		cout << "ErrorSocketConnect!" << endl;
		exit(0);
	}

 	if(listen (listenfdS, LISTENQ) < 0){
 		cout << "ErrorListenClient!" << endl;
 		exit(0);
 	}

 	cout<<"Server running...waiting for connections."<<endl;
  
 	for ( ; ; ) 
 	{
  		clilen = sizeof(cliaddr);
  		connfd = accept (listenfdS, (struct sockaddr *) &cliaddr, &clilen);
  		cout << "SERVER = " << connfd << endl;
  		if(connfd < 0){
  			cout << "ErrorClientConnect!!!" << endl;
  			exit(0);
  		}

  		cout<<"Client connected!"<<endl;

  		mas_thread[COUNT_THREAD] = pthread_create(&mas_id[COUNT_THREAD], NULL, client_thread, &connfd);
  		COUNT_THREAD++;
	}
	
	return 0;
}
