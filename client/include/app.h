#ifndef APP_H
#define APP_H

// Khởi tạo ứng dụng
void init();

// Prompt
void shell_print_prompt();

// Read line
char *shell_read_line();

// exec command from input
void shell_excute(char *line);

// Shutdown app
void shutdown();


#endif