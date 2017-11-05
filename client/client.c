#include "client.h"
/*************信号处理函数***************/
void my_func(int sign_no)
{
	if(sign_no == SIGPIPE)
	{
		printf("i have got SIGPIPE\n");
	}
}
/*****************一级菜单****************/
int menu_1(int *sel)
{
	
	while(1)
	{
		system("clear");
		*sel = 0;	
		printf(SET_COLOR"\t\t|+++++++++++++++++++++++|\n"END_SET);
		printf(SET_COLOR"\t\t|	1、登  录	|\n"END_SET);
		printf(SET_COLOR"\t\t|	2、退  出	|\n"END_SET);
		printf(SET_COLOR"\t\t|+++++++++++++++++++++++|\n"END_SET);

		scanf("%d", sel);
		getchar(); //吃掉回车
		
		if(*sel > 0 && *sel < 3 )
		{
			return 0;
		}

		printf("输入错误,请按回车重新输入\n");
		getchar();
		continue;
	}
}


int main()
{
/**********设置信号处理函数***********************/
	struct sigaction action;
	sigaction(SIGPIPE, 0, &action);
	action.sa_handler = my_func;
	sigaction(SIGPIPE, &action, 0);


/****************设置网络相关*********************/
	struct sockaddr_in sevr_addr;
	bzero(&sevr_addr, sizeof(sevr_addr));
	sevr_addr.sin_family = AF_INET;
	sevr_addr.sin_port = htons(6666);
	sevr_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sevr_fd;
	int sel; //菜单选择
	int exit_status = 0;//退出状态
	if((sevr_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket failed");
		return -1;
	}
	printf("sevr_fd = %d\n",sevr_fd);
	if(connect(sevr_fd, (struct sockaddr *)&sevr_addr, sizeof(sevr_addr)) == -1)
	{
		perror("connect failed");
		return -1;
	}
	while(1)
	{
		menu_1(&sel);
		switch(sel)
		{
		case 1:
			{
				send(sevr_fd, (void *)&sel, sizeof(int), 0);
				exit_status = login(sevr_fd);
				break;
			}
		default:
			send(sevr_fd, (void *)&sel, sizeof(int), 0);
			return OK;
		}
		if(exit_status == -1)
			break;
	}
	close(sevr_fd);
	return 0;
}
