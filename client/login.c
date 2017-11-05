#include "client.h"


int menu_admin(int *sel)
{

	while(1)
	{
		system("clear");
		*sel = 0;
		printf(SET_COLOR"\t\t|+++++++++++++++++++++++++++++++++++|\n"END_SET);
		printf(SET_COLOR"\t\t|	1、添 加 用 户              |\n"END_SET);
		printf(SET_COLOR"\t\t|	2、删 除 用 户              |\n"END_SET);
		printf(SET_COLOR"\t\t|	3、修 改 用 户 信 息        |\n"END_SET);
		printf(SET_COLOR"\t\t|	4、查 询 用 户 信 息        |\n"END_SET);
		printf(SET_COLOR"\t\t|	5、查 看 日 志 信 息        |\n"END_SET);
		printf(SET_COLOR"\t\t|	6、退    出                 |\n"END_SET);
		printf(SET_COLOR"\t\t|+++++++++++++++++++++++++++++++++++|\n"END_SET);
		
		scanf("%d", sel);
		
		getchar(); 
		if(*sel > 0 && *sel < 7 )
		{
			return 0;
		}

		printf("输入错误,请按回车重新输入\n");
		getchar();


	}

}
int menu_normal(int *sel)
{

	while(1)
	{
		system("clear");
		*sel = 0;
		printf(SET_COLOR"\t\t|+++++++++++++++++++++++++++++|\n"END_SET);
		printf(SET_COLOR"\t\t|	1、查 询 用 户 信 息  |\n"END_SET);
		printf(SET_COLOR"\t\t|	2、修  改  密  码     |\n"END_SET);
		printf(SET_COLOR"\t\t|	3、退    出           |\n"END_SET);
		printf(SET_COLOR"\t\t|+++++++++++++++++++++++++++++|\n"END_SET);
		
		scanf("%d", sel);
		getchar(); 
		if(*sel > 0 && *sel < 4 )
		{
			return 0;
		}

		printf("输入错误,请按回车重新输入\n");
		getchar();


	}

}


int login(int sevr_fd)
{
	USER usr_login;
	int state;
	int try_num;
	int sel;
	
	
	for(try_num = 0; try_num < 3; try_num++)
	{
		bzero(&usr_login, sizeof(USER));
		printf("请输入用户名：");
		scanf("%s", usr_login.name);
		printf("请输入密码：");
		scanf("%s", usr_login.password);

		send(sevr_fd, (void *)&usr_login, sizeof(USER), 0);

		state = recv(sevr_fd, (void *)&usr_login, sizeof(USER), 0);
		if(state == -1)
		{
			printf("send failed\n");
			return -1;
		}
		if(state == 0)
		{

			printf("server disconnection\n");
			return -1;
		}

		switch(usr_login.type)
		{
		case 0:
			while(1)
			{
				menu_admin(&sel);
				send(sevr_fd, (void *)&sel, sizeof(int), 0);
				switch(sel)
				{
					case 1:
						adduser(sevr_fd, usr_login);
						break;
					case 2:
						deleuser(sevr_fd);
						break;
					case 3:
						changuser(sevr_fd, usr_login);
						break;
					case 4:
						queryuser(sevr_fd, usr_login);
						break;
					case 5:
						hist(sevr_fd);
						break;
					default:

						return OK;
				}
			}
			break;
		case 1:
			while(1)
			{
				menu_normal(&sel);
				send(sevr_fd, (void *)&sel, sizeof(int), 0);
				switch(sel)
				{
					case 1:
						queryuser(sevr_fd, usr_login);
						break;
					case 2:
						changuser(sevr_fd, usr_login);
						break;
					default:
						return OK;
				}
			}
			
			break;
		case -1:
			printf("用户不存在\n");
			break;
		case -2:
			printf("密码错误\n");
			break;
		default:
			break;
		}

	}
	 
	return 0;
}
