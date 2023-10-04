CC=gcc
CFLAGS=-g -Wall -pedantic
OLIBSFLAGS=-lreadline -lhistory 
LIBFLAGS=$(OLIBSFLAGS) 
LDFLAGS =
TARGET = pasta

all: 	shell 		\
	00_fork_dup_pipe_exec \
	00_execvp_example \
	$(TARGET)


00_execvp_example : 00_execvp_example.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBFLAGS)

00_fork_dup_pipe_exec :  00_fork_dup_pipe_exec.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBFLAGS)

rlbasic : rlbasic.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBFLAGS)

histexamp : histexamp.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBFLAGS)

shell:	shell.o parse.o parse.h
	$(CC) $(CFLAGS) -o $@ shell.o parse.o $(LIBFLAGS)

yosh:   yosh.o parse.o parse.h
	$(CC) $(CFLAGS) -o $@ yosh.o parse.o $(LIBFLAGS)

gosh:   gosh.o 
	$(CC) $(CFLAGS) -o $@ gosh.o $(LIBFLAGS)


$(TARGET): pasta.o pastap.o exp.o
	$(CC) $(LDFLAGS) -o $@ $^

pasta.o: pasta.c pastap.h exp.h
	$(CC) $(CFLAGS) -c -o $@ pasta.c

pastap.o: pastap.c pastap.h
	$(CC) $(CFLAGS) -c -o $@ pastap.c

exp.o: exp.c exp.h pastap.h
	$(CC) $(CFLAGS) -c -o $@ exp.c






# generic
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f pasta *.o
	rm -f shell *~ 
	rm -f pipe
	rm -f *.o
	rm -f rlbasic 
	rm -f histexamp 
	rm -f 00_execvp_example
	rm -f 00_fork_dup_pipe_exec
