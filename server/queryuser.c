#include "server.h"

int queryuser(int clnt_fd, sqlite3 *db, USER *user_data)
{
	INFO user_info;
	MSG r_msg;
	int state;
	char commond[512];
	char *errmsg;
	char **resultp;
	int nrow,ncolumn;
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
		bzero(commond, sizeof(commond));
		sprintf(commond, "select * from main where sno=%d",user_info.no);
		if(sqlite3_get_table(db, commond, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
		{
			printf("%s\n",errmsg);
			sqlite3_free(errmsg);
			return 0;
		}
		if(nrow == 0)
		{
			sprintf(r_msg.mmsg, "没有这个员工");
			r_msg.type = -1;
			send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);

		}

		else
		{
			r_msg.type = 0;
			send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);

			user_info.no = atoi(resultp[8]);
			sprintf(user_info.name,"%s", resultp[9]); 
			sprintf(user_info.sex,"%s", resultp[10]); 
			sprintf(user_info.addr,"%s", resultp[11]);
			user_info.age = atoi(resultp[12]);
			user_info.level = atoi(resultp[13]);
			sprintf(user_info.phone,"%s", resultp[14]);
			user_info.salary = atof(resultp[15]);

			send(clnt_fd, (void *)&user_info, sizeof(INFO), 0);
		}

	}
	else
	{
		bzero(commond, sizeof(commond));
		sprintf(commond, "select * from main where sno=%d",user_data->no);
		if(sqlite3_get_table(db, commond, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
		{
			printf("%s\n",errmsg);
			sqlite3_free(errmsg);
			return 0;
		}
		if(nrow == 0)
		{
			sprintf(r_msg.mmsg, "没有这个员工");
			r_msg.type = -1;
			send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);

		}

		else
		{
			r_msg.type = 0;
			send(clnt_fd, (void *)&r_msg, sizeof(MSG), 0);

			user_info.no = atoi(resultp[8]);
			sprintf(user_info.name,"%s", resultp[9]); 
			sprintf(user_info.sex,"%s", resultp[10]); 
			sprintf(user_info.addr,"%s", resultp[11]);
			user_info.age = atoi(resultp[12]);
			user_info.level = atoi(resultp[13]);
			sprintf(user_info.phone,"%s", resultp[14]);
			user_info.salary = atof(resultp[15]);

			send(clnt_fd, (void *)&user_info, sizeof(INFO), 0);
		}
		
					
	}
	bzero(commond, sizeof(commond));
	sprintf(commond,"insert into hist(sno,sname,sopera) values(%d,'%s','查询')",user_data->no,user_data->name);
	if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		sqlite3_free(errmsg);
		return 0;

	}					
	sqlite3_free_table(resultp);
	return 0;
}
