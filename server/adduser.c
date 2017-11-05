#include "server.h"

int adduser(int clnt_fd, sqlite3 *db, USER *user_data)
{
	printf("adduser\n");
	INFO user_info;
	MSG r_msg;
	int state;
	char commond[512];
	char *errmsg;

	char name[128];
	sprintf(name,"%s", user_data->name);
	int no;
	no = user_data->no;

	state = recv(clnt_fd, (void *)&user_info, sizeof(INFO), 0);
	if(state < 0)
	{
		printf("与客户端连接出错\n");
		return -1;
	}
	else if(0 == state)
	{
		printf("客户端关闭链接\n");
		return -1;
	}

	state = recv(clnt_fd, (void *)user_data, sizeof(USER), 0);
	if(state < 0)
	{
		printf("与客户端连接出错\n");
		return -1;
	}
	else if(0 == state)
	{
		printf("客户端关闭链接\n");
		return -1;
	}

	bzero(commond, sizeof(commond));
	sprintf(commond, "insert into main values(%d,'%s','%s','%s',%d,%d,'%s',\
		%lf)",user_info.no, user_info.name, user_info.sex, user_info.addr,\
		user_info.age, user_info.level, user_info.phone, user_info.salary);
	if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		sprintf(r_msg.mmsg, "%s", errmsg);
		sqlite3_free(errmsg);
		send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
		return ERROR;
	}

	bzero(commond, sizeof(commond));
	sprintf(commond, "insert into user(sno,stype,sname) values(%d,%d,'%s')", user_data->no,user_data->type, user_data->name);
	if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		sprintf(r_msg.mmsg,"%s", errmsg);
		sqlite3_free(errmsg);
		send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
		return ERROR;
	}
	sprintf(r_msg.mmsg, "添加成功");
	send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
	bzero(commond, sizeof(commond));
	sprintf(commond,"insert into hist(sno,sname,sopera) values(%d,'%s','添加用户')",no,name);
	if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		sqlite3_free(errmsg);
		return 0;

	}					





	return 0;
}
