#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <experimental/filesystem>

using namespace std;
namespace fs = std::experimental::filesystem;

int create_socket(int,char *);

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

#define MAXLINE 512 /*max text line length*/

char *mas_filename = new char[MAXLINE];
int counter = 0;

int main(int argc, char **argv)
{
 	int sockfd;
 	struct sockaddr_in servaddr;
 	char sendline[MAXLINE], recvline[MAXLINE];

	if (argc !=3) {
  		cerr<<"Usage: ./a.out <IP address of the server> <port number>"<<endl;
  		exit(1);
 	}

 	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  		cerr<<"Problem in creating the socket"<<endl;
  		exit(2);
 	}

 	memset(&servaddr, 0, sizeof(servaddr));
 	servaddr.sin_family = AF_INET;
 	servaddr.sin_addr.s_addr= inet_addr(argv[1]);
 	servaddr.sin_port =  htons(atoi(argv[2]));

 	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
  		cerr<<"Problem in connecting to the server"<<endl;
  		exit(3);
 	}

 	cerr << "SUCCESFULLY CONNECT!" << endl;

	while (fgets(sendline, MAXLINE, stdin) != NULL) {

		send(sockfd, sendline, MAXLINE, 0);
	  	char *token,*dummy;
	  	dummy=sendline;
	  	token=strtok(dummy," ");
	   
	   	if (strcmp("quit\n",sendline)==0)  {  /////////   QUIT
	   		close(sockfd);
			return 0;
	   	}

   	   	else if (strcmp("cd",token)==0)  {   /////////   PWD
			char check[MAXLINE];
			token=strtok(NULL," \n");
			cout<<"Path given is: "<<token<<endl;
			recv(sockfd,check,MAXLINE,0);
			
			if(strcmp("0",check)==0){
				cerr<<"Directory doesn't exist. Check Path"<<endl;
			}
   	   }

  	   	else if (strcmp("!cd",token)==0)  {   /////////   !CD
			token=strtok(NULL," \n");
			cout<<"Path given is: "<<token<<endl;
			if(chdir(token)<0){
				cerr<<"Directory doesn't exist. Check path"<<endl;
			}
   		}

   	   	else if (strcmp("put",token)==0)  {   /////////   PUT
   	
   			char port[MAXLINE];
   			char buffer[MAXLINE];
   			char char_num_blks[MAXLINE];
   			char char_num_last_blk[MAXLINE]; 
   			char namefile[MAXLINE];			
   			
			char buf_pop[60], buf_push[60];
		    getcwd(buf_pop, sizeof(buf_pop));
		    getcwd(buf_push, sizeof(buf_push));

   			int data_port, datasock, lSize, num_blks, num_last_blk;
			
			FILE *fp;
			
			recv(sockfd, port, MAXLINE,0);

			data_port=atoi(port);
			datasock=create_socket(data_port,argv[1]);
			token=strtok(NULL," \n");
		
			if (fs::is_directory (token))
			{
				strcat(strcat(buf_pop, "/"), token);
				chdir(buf_pop);

				cout<<"direct"<<endl;    

				for (fs::recursive_directory_iterator i (buf_pop), end; i!=end; i++)
				{
					if ((fp=fopen(i->path().filename().c_str(),"rb"))!=NULL)
					{
						send(sockfd,"1",MAXLINE,0);
						send(sockfd, i->path().filename().c_str(), MAXLINE,0);
						cout << i->path().filename().c_str() << endl;
						fseek (fp , 0 , SEEK_END);
						lSize = ftell (fp);
						rewind (fp);
						num_blks = lSize/MAXLINE;
						num_last_blk = lSize%MAXLINE; 
						sprintf(char_num_blks,"%d",num_blks);
						send(sockfd, char_num_blks, MAXLINE, 0);
			
						for(int i= 0; i < num_blks; i++) { 
							fread (buffer,1,MAXLINE,fp);
							send(datasock, buffer, MAXLINE, 0);
						}

						sprintf(char_num_last_blk,"%d",num_last_blk);
						send(sockfd, char_num_last_blk, MAXLINE, 0);
					
						if (num_last_blk > 0) { 
							fread (buffer,1,num_last_blk,fp);
							send(datasock, buffer, MAXLINE, 0);
						}
						fclose(fp);
						cout<<"File upload done.\n";
					}

					else{
						send(sockfd,"0",MAXLINE,0);
						cerr<<"Error in opening file. Check filename\nUsage: put filename"<<endl;
					}
					counter++;
				}
			send(sockfd,"0",MAXLINE,0);
			chdir(buf_push);	
			}
			else
				cout <<"Not Directory!!!"<< endl;
		}

   		else if (strcmp("get",token)==0)  {   /////////   GET

		   	char port[MAXLINE]; 
		   	char buffer[MAXLINE];
		   	char char_num_blks[MAXLINE];
		   	char char_num_last_blk[MAXLINE];
		   	char check[MAXLINE];
			char namefile[MAXLINE];
			
			char buf_pop[60], buf_push[60];
			getcwd(buf_pop, sizeof(buf_pop));
			getcwd(buf_push, sizeof(buf_push));

			int data_port, datasock, lSize, num_blks, num_last_blk, i;
			
			FILE *fp;

			recv(sockfd, port, MAXLINE,0);
			
			data_port=atoi(port);
			
			datasock=create_socket(data_port,argv[1]);
			
			token=strtok(NULL," \n");
			
			mkdir(token, 0777);
			strcat(strcat(buf_pop, "/"), token);
			chdir(buf_pop);

			while(true)
			{
				recv(sockfd, check ,MAXLINE,0);
				if(strcmp("1",check)==0){
					recv(sockfd, namefile, MAXLINE, 0);
					if((fp=fopen(namefile,"wb"))==NULL){
						cout<<"Error in creating file\n";
						break;
					}
					else
					{
						recv(sockfd, char_num_blks, MAXLINE,0);
						num_blks=atoi(char_num_blks);
						
						for(i = 0; i < num_blks; i++) { 
							recv(datasock, buffer, MAXLINE,0);
							fwrite(buffer, 1, MAXLINE, fp);
						}
						
						recv(sockfd, char_num_last_blk, MAXLINE,0);
						num_last_blk=atoi(char_num_last_blk);
						
						if (num_last_blk > 0) { 
							recv(datasock, buffer, MAXLINE,0);
							fwrite(buffer, 1, num_last_blk, fp);
						}
						fclose(fp);
						cout<<"File download done."<<endl;
					}
				}
				else{
					cout << "ErrorFileTo" << endl;
					chdir(buf_push);	
					break;
				}
			}
		}
		else{
			cerr<<"Error in command. Check Command"<<endl;
   		}
  		
  		cout<<"ftp>";

 	}

 exit(0);
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
	 servaddr.sin_port =  htons(port); //convert to big-endian order

	 //Connection of the client to the socket
	 
	 socklen_t clen = sizeof(servaddr);
	 if (connect(sockfd, (struct sockaddr *) &servaddr, clen)<0) {
	  	cerr<<"Problem in creating data channel"<<endl;
	  	exit(3);
	 }

return(sockfd);
}
