#include <unistd.h>
#include <sys/socket.h>

#include "../../include/transport.h"

// todo : sau này thêm chức năng mã hóa kênh truyền
ssize_t net_send(int sockfd, const void* buf, size_t len, int flag) {
    return send(sockfd, buf, len, flag);
}

ssize_t net_recv(int sockfd, void *buf, size_t len, int flag) {
    return recv(sockfd, buf, len, flag);
}