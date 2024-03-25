#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
typedef int socklen_t; // Define a custom type for socklen_t
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

#define SIZE 1024
#define port 8080
#define ip "127.0.0.1"
void terminate_connection(int sockfd) {
    printf("[+]Terminating connection.\n");
#ifdef _WIN32
    const char* terminate_msg = "[+]Terminating connection.\n";
    send(sockfd, terminate_msg, strlen(terminate_msg), 0);
    closesocket(sockfd);
    WSACleanup();
#else
    const char* terminate_msg = "[+]Terminating connection.\n";
    write(sockfd, terminate_msg, strlen(terminate_msg));
    close(sockfd);
#endif
    exit(EXIT_SUCCESS);
}

void write_file(int sockfd)
{
    int n; 
    FILE *fp;
    char *filename = "server_log_file.log";
    char buffer[SIZE];

    fp = fopen(filename, "w");
    
    if(fp==NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }
    while((n = recv(sockfd, buffer, SIZE, 0)) > 0)
    {
        fprintf(fp, "%s", buffer);
        // printf("Received %d bytes: %s\n", n, buffer);
        memset(buffer, 0, SIZE);
        break;
    }
    if (n < 0) {
        perror("[-]Error in recv.");
    }
    fclose(fp); // close the file
    return;
}

int main ()
{
    int e;
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        printf("[-] Error in WSAStartup: %d\n", WSAGetLastError());
        exit(1);
    }
#endif

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
     printf("[+]Server socket created. \n");

     server_addr.sin_family = AF_INET;
     server_addr.sin_port = port;
     server_addr.sin_addr.s_addr = inet_addr(ip);

     e = bind(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
     if(e<0)
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     printf("[+]Binding Successful.\n");

     e = listen(sockfd, 10);
     if(e==0)
     {
         printf("[+]Listening...\n");
     }
     else 
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     addr_size = sizeof(new_addr);
     new_sock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);
     write_file(new_sock);
     printf("[+]Data written in the text file \n");
     terminate_connection(sockfd);
     
}