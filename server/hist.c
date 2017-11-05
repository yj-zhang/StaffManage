#include "server.h"

int hist(int clnt_fd, sqlite3 *db)
{
	char commond[512];
	int state;
	char *errmsg;
	char **resultp;
	int nrow,ncolumn;
	HIST log;
	int i,j;

	bzero(commond, sizeof(commond));
	sprintf(commond, "select * from hist");
	if(sqlite3_get_table(db, commond, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		sqlite3_free(errmsg);
		return 0;
	}
	send(clnt_fd, (void *)&nrow, sizeof(int), 0);
	for(i = 0,j = 4; i < nrow; i++, j++)
	{
		log.no = atoi(resultp[j]);
		strcpy(log.name, resultp[j+1]);
		strcpy(log.oper, resultp[j+2]);
		strcpy(log.date, resultp[j+3]);
		j += 3;
		send(clnt_fd, (void *)&log, sizeof(HIST), 0);

			
	}

	sqlite3_free_table(resultp);
	return 0;
}
