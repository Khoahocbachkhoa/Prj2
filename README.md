# Secure File Sharing System

## Giới thiệu

Secure File Sharing System là ứng dụng chia sẻ tệp tin theo mô hình Client-Server được xây dựng bằng ngôn ngữ C.

Hệ thống hỗ trợ:

* Đăng ký và đăng nhập tài khoản.
* Quản lý thư mục và tệp tin.
* Upload và download tệp tin.
* Chia sẻ tệp tin và thư mục cho người dùng khác.
* Phân quyền Viewer / Editor.
* Truyền dữ liệu qua kênh TLS sử dụng OpenSSL.
* Lưu trữ metadata bằng PostgreSQL.

---

## Yêu cầu

### Server

* Linux
* GCC
* PostgreSQL
* OpenSSL

### Client

* Linux
* GCC
* OpenSSL

---

## Cấu trúc thư mục

```text
server/
├── src/
├── include/
├── certs/
│   ├── server.crt
│   └── server.key
└── Makefile

client/
├── src/
├── include/
├── certs/
│   └── ca.crt
└── Makefile
```

---

## Biên dịch

### Server

```bash
make
```

### Client

```bash
make
```

---

## Chạy chương trình

### Khởi động server

```bash
./server.out 8080
```

### Kết nối client

```bash
./client.out 127.0.0.1 8080
```

---

## Các lệnh hỗ trợ

### Xác thực

```text
register
login
logout
```

### Quản lý thư mục

```text
pwd
ls
cd
mkdir
rmdir
mv
rm
```

### Truyền tệp

```text
put
get
```

### Chia sẻ

```text
share-file
unshare-file

share-folder
unshare-folder

file-acl
folder-acl

shared-files
shared-folders

get-shared

open-shared
exit-shared
```

### Hệ thống

```text
help
quit
```

---

## Bảo mật

Hệ thống sử dụng TLS thông qua thư viện OpenSSL.

Server sử dụng chứng chỉ số được ký bởi Root CA tự tạo.

Client xác thực chứng chỉ của Server trước khi thiết lập phiên làm việc.

Toàn bộ dữ liệu đăng nhập, lệnh điều khiển và nội dung tệp được truyền qua kênh mã hóa TLS.

---

## Tác giả

* Họ tên: ...
* Môn học: Lập trình mạng và An toàn thông tin
* Năm học: ...
