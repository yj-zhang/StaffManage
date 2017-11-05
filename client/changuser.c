#include "client.h"

int changuser(int sevr_fd, USER usr_login)
{
	MSG r_msg;
	INFO user_info;
	//	USER user_data;
	int state;
	system("clear");
	if(usr_login.type == 0)
	{
		printf("请输入要修改的员工工号\n");
		scanf("%d", &user_info.no);
		getchar();
		printf("请输入员工姓名\n");
		scanf("%s",user_info.name);
		getchar();
		printf("请输入员工性别\n");
		scanf("%s",user_info.sex);
		getchar();
		printf("请输入员工地址\n");
		scanf("%s",user_info.addr);
		getchar();
		printf("请输入员工年龄\n");
		scanf("%d",&user_info.age);
		getchar();
		printf("请输入员工等级\n");
		scanf("%d",&user_info.level);
		getchar();
		printf("请输入员工电话\n");
		scanf("%s",user_info.phone);
		getchar();
		printf("请输入员工工资\n");
		scanf("%lf",&user_info.salary);
		getchar();
		printf("请输入员工权限\n");
		scanf("%d",&usr_login.type);
		getchar();

		usr_login.no = user_info.no;
		strcpy(usr_login.name, user_info.name);

		send(sevr_fd, (void *)&user_info, sizeof(INFO), 0);
		send(sevr_fd, (void *)&usr_login, sizeof(USER), 0);
	}
	else
	{
		printf("请输入要新的密码\n");
		scanf("%s", usr_login.password);
		getchar();
		send(sevr_fd, (void *)&usr_login, sizeof(USER), 0);



	}
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
	printf("%s\n请输入回车继续\n", r_msg.mmsg);
	getchar();

	return 0;
}
