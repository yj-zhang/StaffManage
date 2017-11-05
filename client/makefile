CC := gcc
RM := rm -f -v
all : clean client
client : client.o adduser.o changuser.o deleuser.o login.o queryuser.o hist.o	
	$(CC) $^ -o $@
.c.o :
	$(CC) -c $<
.PHONY : clean
clean:
	$(RM) *.o client
	


