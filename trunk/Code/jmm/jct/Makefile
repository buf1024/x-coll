CC = cc
CCFLAGS = -O2 -Wall -g3

JCT=jct

JCT_MY_OBJ=

JCT_OBJ=jct.o jct_proc.o jct_event.o \
		$(JCT_MY_OBJ)

EXT_CCFLAGS = -levent_core

all:$(JCT)

$(JCT):$(JCT_OBJ)
	$(CC) $(EXT_CCFLAGS) -o $@ $(JCT_OBJ)

install:all
	cp -f $(JCT) ./bin

clean:
	rm -rf *.o
	rm -rf $(JCT)

.PRECIOUS:%.c
.SUFFIXES:
.SUFFIXES:.c .o
.c.o:
	$(CC) $(CCFLAGS) -c -o $*.o $<

