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

## Cài đặt cơ sở dữ liệu

### Tạo database

Đăng nhập PostgreSQL:

```bash
psql -U postgres
```

Tạo database:

```sql
CREATE DATABASE file_sharing_db;
```

Thoát:

```sql
\q
```

### Import schema

```bash
psql -U postgres -d file_sharing_db -f schema.sql
```

Kiểm tra:

```bash
psql -U postgres -d file_sharing_db
```

Liệt kê bảng:

```sql
\dt
```

---

## Thiết lập TLS

Hệ thống sử dụng OpenSSL và chứng chỉ được ký bởi Root CA tự tạo.

### 1. Tạo Root CA

Tạo khóa riêng:

```bash
openssl genrsa -out ca.key 2048
```

Tạo chứng chỉ CA:

```bash
openssl req -x509 \
    -new \
    -nodes \
    -key ca.key \
    -sha256 \
    -days 3650 \
    -out ca.crt
```

---

### 2. Tạo khóa riêng cho Server

```bash
openssl genrsa -out server.key 2048
```

---

### 3. Tạo Certificate Signing Request (CSR)

```bash
openssl req -new \
    -key server.key \
    -out server.csr
```

---

### 4. Ký chứng chỉ Server bằng Root CA

```bash
openssl x509 \
    -req \
    -in server.csr \
    -CA ca.crt \
    -CAkey ca.key \
    -CAcreateserial \
    -out server.crt \
    -days 3650 \
    -sha256
```

### 5. Kiểm tra chứng chỉ

```bash
openssl verify \
    -CAfile ca.crt \
    server.crt
```

Kết quả mong đợi:

```text
server.crt: OK
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