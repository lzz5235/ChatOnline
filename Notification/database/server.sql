CREATE TABLE friend
(
	id  INTEGER NOT NULL,
	friendname  VARCHAR(20) NULL,
	friendid  INTEGER NULL
)
;


ALTER TABLE friend
	ADD  PRIMARY KEY (id)
;


CREATE TABLE tmp
(
	id  INTEGER NOT NULL,
	fromfriend  VARCHAR(20) NULL,
	fromfriendid  INTEGER NULL,
	tofriend  VARCHAR(20) NULL,
	tofriendid  INTEGER NULL,
	message  VARCHAR(20) NULL,
	messagetype  INTEGER NULL
)
;


ALTER TABLE tmp
	ADD  PRIMARY KEY (id)
;


CREATE TABLE user
(
	id  INTEGER NULL,
	nickname  CHAR(18) NULL,
	account  CHAR NULL,
	password  CHAR(18) NULL,
	description  LONG VARCHAR NULL,
	status  INTEGER NULL,
	mobilephone  INTEGER NULL,
	officephone  INTEGER NULL,
	dormitory  VARCHAR(20) NULL,
	mail  VARCHAR(20) NULL,
	location  VARCHAR(20) NULL,
	lastlogintime  DATE NULL,
	registertime  CHAR(18) NULL,
	birthday  INTEGER NULL
)
;


ALTER TABLE user
	ADD  PRIMARY KEY (id)
;


ALTER TABLE friend
	ADD FOREIGN KEY R_2 (id) REFERENCES user(id)
;


ALTER TABLE tmp
	ADD FOREIGN KEY R_3 (id) REFERENCES user(id)
;