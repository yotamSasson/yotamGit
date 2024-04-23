TARGET = a.out
TARGET_LIB = libwd.so
TARGET_WD = wd.out
CC = gcc
SOURCE = ./src/wd.c ./src/libwd.c ../scheduler/src/sched.c ../scheduler/src/uid.c ../scheduler/src/task.c ../../c-data-structures/src/heap_pq.c ../../c-data-structures/src/dynamic_vector.c ../../c-data-structures/src/heap.c
TEST = ./test/wd_client.c
CPPFLAGS = -I./include/ -I../../c-data-structures/include/ -I../scheduler/include/
CFLAGS =  -pthread -fPIC
LDFLAGS =-L. -Wl,-rpath=. 
TEST_OBJS = wd_client.o
WD_OBJS = wd.o
OBJS = libwd.o sched.o uid.o task.o heap_pq.o dynamic_vector.o heap.o 

all: $(TARGET_WD)
all: $(TARGET) 
all: $(TARGET_LIB) 

$(TARGET_WD): $(TARGET_LIB) $(WD_OBJS)
	$(CC)  -o $@ $(WD_OBJS) $(LDFLAGS) -lwd

$(TARGET): $(TEST_OBJS) $(TARGET_LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(TEST_OBJS) $(LDFLAGS) -lwd

$(TARGET_LIB): $(OBJS) $(WD_OBJS) 
	$(CC) -shared -o $@ $^

$(OBJS): $(SOURCE) 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^ 

$(TEST_OBJS): $(TEST) 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^

$(WD_OBJS): $(SOURCE)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^ 

debug: CFLAGS += -g 
debug: $(TARGET_WD) $(TARGET) $(TARGET_LIB)

release: CFLAGS += -O3 
release: $(TARGET_WD) $(TARGET) $(TARGET_LIB)

.PHONY: update
update:
	touch $(SOURCE) $(TEST)
	
.PHONY:  clean
clean:
	rm $(TEST_OBJS) $(OBJS) $(TARGET) $(TARGET_WD) $(TARGET_LIB) $(WD_OBJS)
