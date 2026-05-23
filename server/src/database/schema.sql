-- todo: Sau này thêm bảo mật
create table users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT NOW()
);

-- Thư mục
create table folders (
    id BIGSERIAL PRIMARY KEY,

    owner_id INTEGER NOT NULL -- chủ sỡ hữu của thư mục
        REFERENCES users(id)
        ON DELETE CASCADE,

    parent_id BIGINT -- Thư mục cha
        REFERENCES folders(id)
        ON DELETE CASCADE, 

    name VARCHAR(255) NOT NULL,

    created_by INTEGER
        REFERENCES users(id),

    updated_by INTEGER
        REFERENCES users(id),

    deleted_at TIMESTAMP,

    created_at TIMESTAMP DEFAULT NOW(),
    updated_at TIMESTAMP DEFAULT NOW()
);

-- Tệp tin
CREATE TABLE files (
    id BIGSERIAL PRIMARY KEY,

    owner_id INTEGER NOT NULL -- chủ sở hữu file
        REFERENCES users(id)
        ON DELETE CASCADE,

    folder_id BIGINT -- Thư mục cha
        REFERENCES folders(id)
        ON DELETE CASCADE,

    filename VARCHAR(255) NOT NULL,

    storage_key TEXT NOT NULL, -- định danh file trên storage backend

    size BIGINT NOT NULL DEFAULT 0,

    mime_type VARCHAR(255), -- kiểu mime

    created_by INTEGER
        REFERENCES users(id),

    updated_by INTEGER
        REFERENCES users(id),

    deleted_at TIMESTAMP,

    created_at TIMESTAMP DEFAULT NOW(),

    updated_at TIMESTAMP DEFAULT NOW()
);

-- Phân quyền
create table permissions (
    id BIGSERIAL PRIMARY KEY,
    resource_type VARCHAR(10) NOT NULL, -- file hoặc folder
    resource_id BIGINT NOT NULL, -- định dạnh file hoặc folder đó
    target_user_id INTEGER NOT NULL -- chỉ user_id được nhắm tới
        REFERENCES users(id)
        ON DELETE CASCADE,
    role VARCHAR(20) NOT NULL, -- viewer: chỉ được phép list, cd và download file về
                               -- editor: có thể xóa, sửa, cập nhật file tùy ý
    created_by INTEGER
        REFERENCES users(id),

    created_at TIMESTAMP DEFAULT NOW()
);

-- audit
CREATE TABLE audit_logs (
    id BIGSERIAL PRIMARY KEY,

    actor_user_id INTEGER
        REFERENCES users(id),

    action VARCHAR(50) NOT NULL,
    -- upload
    -- delete
    -- rename
    -- move
    -- mkdir

    resource_type VARCHAR(10) NOT NULL, -- file hoặc folder
    resource_id BIGINT NOT NULL,

    metadata JSONB,

    created_at TIMESTAMP DEFAULT NOW()
);

-- Thêm ràng buộc

-- unique folers name 
ALTER TABLE folders
ADD CONSTRAINT unique_folder_name
UNIQUE(parent_id, owner_id, name);

-- unique file name
ALTER TABLE files
ADD CONSTRAINT unique_file_name
UNIQUE(folder_id, owner_id, filename);

-- unique permissions
ALTER TABLE permissions
ADD CONSTRAINT unique_permission
UNIQUE (
    resource_type,
    resource_id,
    target_user_id
);

-- Thêm check

ALTER TABLE permissions
ADD CONSTRAINT check_role
CHECK (role IN ('viewer', 'editor'));

ALTER TABLE permissions
ADD CONSTRAINT check_resource_type
CHECK (resource_type IN ('file', 'folder'));

ALTER TABLE audit_logs
ADD CONSTRAINT check_audit_resource_type
CHECK (resource_type IN ('file', 'folder'));

-- Thêm chỉ mục

CREATE INDEX idx_folders_parent
ON folders(parent_id);

CREATE INDEX idx_files_folder
ON files(folder_id);

CREATE INDEX idx_permissions_lookup
ON permissions(
    resource_type,
    resource_id,
    target_user_id
);

CREATE INDEX idx_audit_resource
ON audit_logs(
    resource_type,
    resource_id
);