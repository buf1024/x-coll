CC = cc
CCFLAGS = -O2 -Wall -g3

JMM=jmm

JMM_MY_OBJ=myserver.o

JMM_OBJ=ciniconfig.o clog.o \
		jmm.o jmm_conf.o jmm_event.o jmm_proc.o jmm_shm.o jmm_util.o \
		jmm_log.o \
		$(JMM_MY_OBJ)

EXT_CCFLAGS = -lm -levent_core

all:$(JMM)

$(JMM):$(JMM_OBJ)
	$(CC) $(EXT_CCFLAGS) -o $@ $(JMM_OBJ)

install:all
	cp -f $(JMM) ./bin

clean:
	rm -rf *.o
	rm -rf $(JMM)

.PRECIOUS:%.c
.SUFFIXES:
.SUFFIXES:.c .o
.c.o:
	$(CC) $(CCFLAGS) -c -o $*.o $<

