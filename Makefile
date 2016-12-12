obj = client_hf.o commend.o 3des.o getIp.o pro_Key.o mac.o serial_poll.o com_RW.o
#CC = gcc
CC = arm-linux-gcc
all: gataway clean

gataway: $(obj)
	$(CC) -o gataway $(obj) -lpthread

client_hf.o : client_hf.c client_hf.h config.h print.h
	$(CC) -c client_hf.c -lpthread

commend.o : commend.c commend.h config.h  print.h
	$(CC) -c commend.c

3des.o : 3des.c 3des.h config.h
	$(CC) -c 3des.c

getIp.o : getIp.c getIp.h config.h
	$(CC) -c getIp.c

pro_Key.o : pro_Key.c pro_Key.h config.h
	$(CC) -c pro_Key.c

serial_poll.o : serial_poll.c serial_config.h
	$(CC) -c serial_poll.c

com_RW.o : com_RW.c com_RW.h config.h print.h 
	$(CC) -c com_RW.c

mac.o : mac.c mac.h config.h
	$(CC) -c mac.c

.PHONY:clean
clean:
	rm $(obj)
	cp gataway /mnt/hgfs/share/
	rm gataway
