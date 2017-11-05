#include "client.h"

int deleuser(int sevr_fd)
{
	INFO user_info;
	MSG r_msg;
	int state;
	system("clear");
	printf("请输入要删除的员工的工号\n");
	scanf("%d", &user_info.no);
	getchar();
	printf("请输入要删除的员工的姓名\n");
	scanf("%s", user_info.name);
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
	printf("%s\n输入回车继续\n", r_msg.mmsg);
	getchar();



	return 0;
}
