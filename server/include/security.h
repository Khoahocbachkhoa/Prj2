#ifndef SECURITY_H
#define SECURITY_H

#include "database.h"

// Kiểm tra độ mạnh của một mật khẩu
db_errror_code check_password(const char *pass);

#endif