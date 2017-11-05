#include "client.h"

int adduser(int sevr_fd, USER user_data)
{
	INFO user_info;
	MSG r_msg;//接收处理结果
	int state;
	printf("adduser\n");
	system("clear");

	printf("请输入员工工号\n");
	scanf("%d",&user_info.no);
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
	scanf("%d",&user_data.type);
	getchar();

	strcpy(user_data.name, user_info.name);
	user_data.no = user_info.no;

	send(sevr_fd, (void *)&user_info, sizeof(INFO), 0);
	send(sevr_fd, (void *)&user_data, sizeof(USER), 0);

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
	printf("%s\n输入回车继续\n", r_msg.mmsg);
	getchar();

	return 0;
}
