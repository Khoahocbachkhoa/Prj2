#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/app.h"
#include "../../include/command.h"
#include "../../include/parser.h"
#include "../../include/transport.h"
#include "../../include/state.h"
#include "../../include/util.h"

void cmd_upload(ParsedCommand *cmd) {
    if (cmd->argc != 3) {
        printf("Usage: put --path path_to_file\n");
        return;
    }

    if (strcmp(cmd->argv[1], "--path") != 0) {
        printf("Error: unknown option '%s'\n", cmd->argv[1]);
        return;
    }

    char *path = cmd->argv[2];
    // chuẩn hóa path
    char fullpath[512];
    normalize_path(path, fullpath, sizeof(fullpath));

    // Lấy tên file
    char filename[256];
    get_file_name(fullpath, filename, sizeof(filename));

    // validate filename
    if (check_file_name(filename) == false) {
        printf("Invalid filename\n");
        return;
    }

    // Mở file
    FILE *fp = fopen(fullpath, "rb");
    
    if (fp == NULL) {
        perror("fopen");
        return;
    }

    // Lấy kích thước file
    fseek(fp, 0, SEEK_END);

    long filesize = ftell(fp);

    rewind(fp);

    if (filesize < 0) {
        printf("Error: cannot determine file size\n");
        fclose(fp);
        return;
    }

    // Gửi request upload
    char req[512];

    snprintf(req, sizeof(req), "UPLOAD %s %ld\r\n",
            filename, filesize);

    send_command(state->sockfd, req);

    // Đọc phản hồi
    char res[256];

    if (recv_response_to_buf(state->sockfd, res, sizeof(res)) < 0) {
        fclose(fp);
        return;
    }

    // parse response, chỉ stream file khi code là 150 Oke
    int code;
    sscanf(res, "%d", &code);

    if (code != 150) {
        printf("%s", res);
        fclose(fp);
        return;
    }

    // Bắt đầu stream file
    char buffer[8192];
    size_t nread;

    while ((nread = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        // Đảm bảo gửi đủ dữ liệu
        if (net_send_all(state->sockfd, buffer, nread, 0) <= 0) {
            printf("Upload failed\nSome error occured or lost connection to server\n");
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    // Wait for upload success
    recv_response(state->sockfd);
}

void cmd_download(ParsedCommand *cmd) {
    if (cmd == 1) {
        printf("Usage: get <filename> [--path saved_path]\n");
        return;
    }

    
}

void cmd_download_shared(ParsedCommand *cmd) {
    
}