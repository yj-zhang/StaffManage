#include "server.h"


int login(int clnt_fd, sqlite3 *db, USER *user_data)
{



	char *errmsg;
	char commond[512];
	char **resultp;
	int nrow, ncolumn;
	
	int try_num;
	int sel;
	int state;
	
	for(try_num = 0; try_num < 3; try_num++)
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
		else
		{
			bzero(commond, sizeof(commond));
			sprintf(commond, "select * from user where sname = '%s'", user_data->name);
			if(sqlite3_get_table(db, commond, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
			{
				printf("%s\n",errmsg);
				sqlite3_free(errmsg);
				return 0;
			}
			if(nrow == 0)
			{
				user_data->type = -1;
				send(clnt_fd, (void *)user_data, sizeof(USER), 0);

			}
			else
			{
				if(0 == strcmp(user_data->password, resultp[7]))
				{
					user_data->type = atoi(resultp[5]);
					user_data->no = atoi(resultp[4]);
					send(clnt_fd, (void *)user_data, sizeof(USER), 0);
					bzero(commond, sizeof(commond));
					sprintf(commond,"insert into hist(sno,sname,sopera) values(%d,'%s','登录')",user_data->no,user_data->name);
					if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
					{
						printf("%s\n",errmsg);
						sqlite3_free(errmsg);
						return 0;

					}					
					switch(user_data->type)
					{
					case 0:
						while(1)
						{
							state = recv(clnt_fd, (void *)&sel, sizeof(int), 0);
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
							switch(sel)
							{
								case 1:
									adduser(clnt_fd, db, user_data);
									break;
								case 2:
									deleuser(clnt_fd, db, user_data);
									break;
								case 3:
									changuser(clnt_fd, db, user_data);
									break;
								case 4:
									queryuser(clnt_fd, db, user_data);
									break;
								case 5:
									hist(clnt_fd, db);
									break;
								default:
									bzero(commond, sizeof(commond));
									sprintf(commond,"insert into hist(sno,sname,sopera) values(%d,'%s','退出')",user_data->no,user_data->name);
							   		if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
									{
										printf("%s\n",errmsg);
										sqlite3_free(errmsg);
										return 0;

									}					
									return OK;

							 }
						}
						break;
					case 1:
						while(1)
						{
							state = recv(clnt_fd, (void *)&sel, sizeof(int), 0);
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
							switch(sel)
							{
							case 1:
								queryuser(clnt_fd, db, user_data);
								break;
							case 2:
								changuser(clnt_fd, db, user_data);
								break;
							default:
								bzero(commond, sizeof(commond));
								sprintf(commond,"insert into hist(sno,sname,sopera) values(%d,'%s','退出')",user_data->no,user_data->name);
								if(sqlite3_exec(db, commond, NULL, NULL, &errmsg) != SQLITE_OK)
								{
									printf("%s\n",errmsg);
									sqlite3_free(errmsg);
									return 0;

								}					

								return OK;
							}		
						}

						break;
					default:
						return ERROR;
					}

				}
				else
				{
					user_data->type = -2;
					send(clnt_fd, (void *)user_data, sizeof(USER), 0);

				}

			}

		}

	}


	sqlite3_free_table(resultp);
	return 0;
}
