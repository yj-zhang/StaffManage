#include "server.h"

int changuser(int clnt_fd, sqlite3 *db, USER *user_data)
{
	INFO user_info;
	//	USER user_data;
	MSG r_msg;
	char commond[512];
	char *errmsg;
	int state;
	
	int no;
	no = user_data->no;
	char name[128];
	sprintf(name,"%s", user_data->name);

	if(user_data->type == 0)
	{
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
		sprintf(commond, "update main set sname='%s',ssex='%s',saddr='%s',\
				sage=%d,slevel=%d,sphone='%s',ssalary=%lf where sno = '%d'",\
				user_info.name,user_info.sex,user_info.addr,user_info.age,\
				user_info.level,user_info.phone,user_info.salary,user_info.no);
		if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
		{
			sprintf(r_msg.mmsg, "%s", errmsg);
			send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
			sqlite3_free(errmsg);
			return 0;	

		}
		bzero(commond, sizeof(commond));
		sprintf(commond, "update user set stype='%d',sname='%s' where sno=%d",\
				user_data->type, user_data->name, user_data->no);
		if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
		{
			sprintf(r_msg.mmsg, "%s", errmsg);
			send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
			sqlite3_free(errmsg);
			return 0;	

		}
	
	}
	else
	{
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
		sprintf(commond, "update user set spassword='%s' where sno=%d",user_data->password, user_data->no);
		if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
		{
			sprintf(r_msg.mmsg, "%s", errmsg);
			send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
			sqlite3_free(errmsg);
			return 0;	

		}

	}
	sprintf(r_msg.mmsg, "修改成功");
	send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);
					bzero(commond, sizeof(commond));
					sprintf(commond,"insert into hist(sno,sname,sopera) values(%d,'%s','修改')",no,name);
					if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
					{
						printf("%s\n",errmsg);
						sqlite3_free(errmsg);
						return 0;

					}					



	return 0;
}
