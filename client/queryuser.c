#include "client.h"

int queryuser(int sevr_fd, USER usr_login)
{
	MSG r_msg;
	INFO user_info;
	int state;
	if(usr_login.type == 0)
	{
		printf("请输入要查询的员工工号\n");
		scanf("%d", &user_info.no);
		getchar();

		send(sevr_fd, (void *)&user_info, sizeof(INFO), 0);

		state = recv(sevr_fd, (void *)&r_msg, sizeof(MSG), 0);
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
		if(r_msg.type == -1)
		{
			printf("%s\n", r_msg.mmsg);
			return OK;
		}
		else
		{
			state = recv(sevr_fd, (void *)&user_info, sizeof(INFO), 0);
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
			printf("+--------------+\n");
			printf("工号：%d\n", user_info.no);
			printf("+--------------+\n");
			printf("姓名：%s\n", user_info.name);
			printf("+--------------+\n");
			printf("性别：%s\n", user_info.sex);
			printf("+--------------+\n");
			printf("地址：%s\n", user_info.addr);
			printf("+--------------+\n");
			printf("年龄：%d\n", user_info.age);
			printf("+--------------+\n");
			printf("职级：%d\n", user_info.level);
			printf("+--------------+\n");
			printf("电话：%s\n", user_info.phone);
			printf("+--------------+\n");
			printf("工资：%.2lf\n", user_info.salary);
			printf("输入回车继续\n");
			getchar();

		}
	}
	else
	{
		state = recv(sevr_fd, (void *)&r_msg, sizeof(MSG), 0);
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
		if(r_msg.type == -1)
		{
			printf("%s\n", r_msg.mmsg);
			return OK;
		}
		else
		{
			state = recv(sevr_fd, (void *)&user_info, sizeof(INFO), 0);
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
			printf("+--------------+\n");
			printf("工号：%d\n", user_info.no);
			printf("+--------------+\n");
			printf("姓名：%s\n", user_info.name);
			printf("+--------------+\n");
			printf("性别：%s\n", user_info.sex);
			printf("+--------------+\n");
			printf("地址：%s\n", user_info.addr);
			printf("+--------------+\n");
			printf("年龄：%d\n", user_info.age);
			printf("+--------------+\n");
			printf("职级：%d\n", user_info.level);
			printf("+--------------+\n");
			printf("电话：%s\n", user_info.phone);
			printf("+--------------+\n");
			printf("工资：%.2lf\n", user_info.salary);
			printf("输入回车继续\n");
			getchar();
		}
	}
	return 0;
}
