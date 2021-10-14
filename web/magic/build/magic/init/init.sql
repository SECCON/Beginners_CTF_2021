use `db`;

DROP TABLE IF EXISTS `user`;
CREATE TABLE user (
  `id` bigint NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `name` VARCHAR(255) NOT NULL UNIQUE,
  `pass` VARCHAR(255) NOT NULL,
  `magic_token` VARCHAR(255) NOT NULL UNIQUE,
  INDEX idx_name (`name`),
  INDEX idx_magic_token (`magic_token`)
) ENGINE=InnoDB DEFAULT CHARACTER SET utf8mb4;

DROP TABLE IF EXISTS `memo`;
CREATE TABLE memo (
  `id` bigint NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `user_id` int NOT NULL,
  `text` TEXT NOT NULL,
  INDEX idx_user_id (`user_id`)
) ENGINE=InnoDB DEFAULT CHARACTER SET utf8mb4;

REVOKE all privileges ON db.* FROM user;
GRANT SELECT ON db.* TO user;
GRANT INSERT ON db.* TO user;
GRANT DELETE ON db.* TO user;
