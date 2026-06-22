#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#include "../../include/transport.h"

// todo : sau này thêm chức năng mã hóa kênh truyền
ssize_t net_send(int sockfd, const void* buf, size_t len, int flag) {
    return send(sockfd, buf, len, flag);
}

ssize_t net_recv(int sockfd, void *buf, size_t len, int flag) {
    return recv(sockfd, buf, len, flag);
}

int send_command(int sockfd, const char *cmd) {
    net_send(sockfd, cmd, strlen(cmd), 0);
    return 0;
}

int recv_response(int sockfd) {
    char buf[8192];

    // Đọc phản hồi từ server và in kết quả
    int n = net_recv(sockfd, buf, sizeof(buf)-1, 0);
        
    if (n <= 0) {
        return -1;
    }

    buf[n] = '\0';
    printf("%s", buf);
}

// Đọc phản hồi vào buf
int recv_response_to_buf(int sockfd, char *buf, int buf_size) {
    if (buf == NULL || buf_size <= 1)
        return -1;

    int n = net_recv(sockfd, buf, buf_size - 1, 0);

    if (n <= 0)
        return -1;

    buf[n] = '\0';

    return n;
}