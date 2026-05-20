#ifndef SECURITY_H
#define SECURIT_H

#include <unistd.h>

// Nhập mật khẩu không lộ màn hình
void read_password(char *buffer, size_t size);

#endif