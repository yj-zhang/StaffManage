#include "client.h"

int hist(int sevr_fd)
{
	int state;
	HIST log;
	int i,j,nrow;
	state = recv(sevr_fd, (void *)&nrow, sizeof(int), 0);
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
	

	for(i = 0; i < nrow; i++ )
	{
		printf("|-------|--------|-----------|--------------------|\n");
		recv(sevr_fd, (void *)&log, sizeof(HIST), 0);
		printf("|%d\t|%s\t |%s\t     |%s|\n",log.no,log.name,log.oper,log.date);
	}
	printf("输入回车继续\n");
	getchar();
	return 0;
}
