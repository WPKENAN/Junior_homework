create table if not exists userinfo(
id int unsigned auto_increment,
username varchar(20) not null,
pwd varchar(20) not null,
unique (username),
primary key (id)
);

