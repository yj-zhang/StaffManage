CC := gcc
RM := rm -f -v
all : clean server
server : server.o adduser.o changuser.o deleuser.o login.o queryuser.o hist.o	
	$(CC) $^ -lpthread -lsqlite3 -o $@
.c.o :
	$(CC) -c $<
.PHONY : clean
clean:
	$(RM) *.o server
	


