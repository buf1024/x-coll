CC = cc
CCFLAGS = -O2 -Wall -g3

JCC=jcc

JCC_MY_OBJ=

JCC_OBJ=jcc.o jcc_proc.o jcc_event.o \
		$(JCC_MY_OBJ)

EXT_CCFLAGS = -levent_core

all:$(JCC)

$(JCC):$(JCC_OBJ)
	$(CC) $(EXT_CCFLAGS) -o $@ $(JCC_OBJ)

install:all
	cp -f $(JCC) ./bin

clean:
	rm -rf *.o
	rm -rf $(JCC)

.PRECIOUS:%.c
.SUFFIXES:
.SUFFIXES:.c .o
.c.o:
	$(CC) $(CCFLAGS) -c -o $*.o $<

