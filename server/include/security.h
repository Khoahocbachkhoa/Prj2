#ifndef SECURITY_H
#define SECURITY_H

typedef enum {
    PASSWORD_WEAK = 0,
    PASSWORD_STRONG = 1,
    PASSWORD_ERR = 2
} PasswordStrength;

// Kiểm tra độ mạnh của một mật khẩu
PasswordStrength check_password(const char *pass);

#endif