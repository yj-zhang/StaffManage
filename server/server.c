#include "server.h"

/*************线程函数**************************/
void *thrd_func(void * arg)
{
	int clnt_fd;
	char *errmsg;
	clnt_fd = (int)arg;
	sqlite3 *db;
	char commond[512] = {0};
	int sel;
	int exit_status;
	USER user_data;
	int state;
/**************打开数据库和表***********************/
	if(sqlite3_open("staff.db", &db) != SQLITE_OK)
	{
		printf("error:%s\n",sqlite3_errmsg(db));
		exit(-1);
	}
	sprintf(commond,"create table if not exists main(sno integer primary key,sname text not null,ssex text,\
		saddr text not null,sage integer,slevel integer,sphone text,ssalary decimal(8,2))");
	if(sqlite3_exec(db, commond,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("error :  %s\n",  errmsg);
		exit(-1);
	}
	bzero(commond, sizeof(commond));
	sprintf(commond,"create table if not exists user(sno integer primary key,stype integer,name text not null,spassword text not null default '123')");
	if(sqlite3_exec(db, commond,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("error :  %s\n",  errmsg);
		exit(-1);
	}
	bzero(commond, sizeof(commond));
	sprintf(commond,"create table if not exists hist(sno integer not null,sname text not null,sopera text not null,\
		datetime TimeStamp not null default (datetime('now','localtime'))) ");
	if(sqlite3_exec(db, commond,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("error :  %s\n",  errmsg);
		exit(-1);
	}

/*************************************************/
	while(1)
	{
		
		state = recv(clnt_fd, (void *)&sel, sizeof(int), 0);
		if(state < 0)
		{
			printf("与客户端连接出错\n");
			break;	
		}
		else if(0 == state)
		{
			printf("客户端关闭链接\n");
			break;
		}
		else
		{
			if(sel == 2)
				break;
		
			switch(sel)
			{
			case 1:
				
				login(clnt_fd, db, &user_data);
				break;
			default:
				break;
			}
		
			if(exit_status == -1)
				break;
		}
	}
	printf("%s已经退出登录\n",user_data.name);
	close(clnt_fd);
	sqlite3_close(db);

	pthread_exit(NULL);

}



int main()
{
	int lisn_fd;
	int clnt_fd;
	struct sockaddr_in my_addr, cliaddr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(6666);
	my_addr.sin_addr.s_addr = inet_addr("192.168.3.4");
	socklen_t clilen;
	clilen = sizeof(cliaddr);
	pthread_t clnt_thread;
	pthread_attr_t attr;
/***************初始化线程属性对象************************/
	if(pthread_attr_init(&attr) != 0)
	{
		perror("create attribute failed");
		return -ERROR;
	}
/***************设置线程分离属性*********************/
	if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
	{
		perror("setdatachstate failed");
		return -ERROR;
	}
/*********创建套接字*****************************/
	if((lisn_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket:");
		return -ERROR;
	}
	printf("lisn_fd=%d\n",lisn_fd);
/***********绑定 ip  端口**************/
	if(bind(lisn_fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
	{
		perror("bind:");
		return -1;
	}
/**********开启监听**********************/
	if(listen(lisn_fd, 10) == -1)
	{
		perror("listen:");
		return -1;
	}
/***********循环等待客户端链接请求**************/	
	while(1)
	{
		if((clnt_fd = accept(lisn_fd, (struct sockaddr *)&cliaddr, &clilen)) == -1)
		{
			perror("accept:");
			return -1;
		}
		printf("clnt_fd=%d\n",clnt_fd);
		if(pthread_create(&clnt_thread, &attr, thrd_func,(void *)clnt_fd) != 0)
		{
			perror("create thread failed");
			return -1;
		}
		
		//pthread_attr_destroy(&attr);
	}

	pthread_attr_destroy(&attr);
	return 0;
}
