MAKE := make
.PHONY : all
all:
	$(MAKE) -C ./server/
	$(MAKE) -C ./client/

