#include "server.h"

int deleuser(int clnt_fd, sqlite3 *db, USER *user_data)
{
	MSG r_msg;
	INFO user_info;
	int state;
	char *errmsg;
	char commond[512];

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

	bzero(commond, sizeof(commond));
	sprintf(commond, "delete from main where sno = '%d'", user_info.no);
	if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		sprintf(r_msg.mmsg, "%s", errmsg);
		send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
		sqlite3_free(errmsg);
		return 0;	
	}
	bzero(commond, sizeof(commond));
	sprintf(commond, "delete from user where sno = '%d'", user_info.no);
	if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		sprintf(r_msg.mmsg, "%s", errmsg);
		send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
		sqlite3_free(errmsg);
		return 0;	
	}
	sprintf(r_msg.mmsg, "删除成功");
	send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
					bzero(commond, sizeof(commond));
					sprintf(commond,"insert into hist(sno,sname,sopera) values(%d,'%s','删除员工')",user_data->no,user_data->name);
					if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
					{
						printf("%s\n",errmsg);
						sqlite3_free(errmsg);
						return 0;

					}					

	return 0;
}
