-- sau mở rộng lưu password dưới dạng băm

create table users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password TEXT NOT NULL
);

