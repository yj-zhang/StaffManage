#ifndef _STFMANG_
#define _STFMANG_

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <sqlite3.h>
#include <signal.h>
#define OK 0
#define ERROR -1
#define END_SET "\033[0m"
#define SET_COLOR "\033[1;42;34m"

typedef struct
{
	int no;
	int type;//权限标志  0是管理员	1是普通用户	-1代表用户不存在
	char name[128];
	char password[128];
}USER;
typedef struct
{
	int no;
	char name[128];
	char sex[6];
	char addr[128];
	int age;
	int level;
	char phone[64];
	double salary;//工资
}INFO;
typedef struct
{
	int type;
	char mmsg[512];
}MSG;
typedef struct
{
	int no;
	char name[512];
	char oper[512];
	char date[512];
}HIST;
int hist(int);
int login(int);
int adduser(int, USER);
int deleuser(int);
int changuser(int,USER);
int queryuser(int,USER);
#endif
