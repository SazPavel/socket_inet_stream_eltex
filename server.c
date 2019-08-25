#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    char buf[16];
    int sock, bytes_read;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(-1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(-1);
    }
    listen(sock, 1);
    sock = accept(sock, NULL, NULL);
    if(sock < 0)
    {
        perror("sock2");
        exit(-1);
    }
    bytes_read = recv(sock, buf, 16, 0);
    printf("%d %s\n", bytes_read, buf);
    close(sock);
    exit(0);
}
