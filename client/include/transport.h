#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <stdio.h>

// Wrap send và recv để mã hóa kênh truyền sau này
ssize_t net_send(int sockfd, const void* buf, size_t len, int flag);

ssize_t net_recv(int sockfd, void* buf,size_t len, int flag);

#endif