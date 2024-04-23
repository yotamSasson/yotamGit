TARGET = a.out
TARGET_LIB = libsched_utils.so
CC = gcc
SOURCE = ./src/sched.c ./src/uid.c ./src/task.c ../../c-data-structures/src/heap_pq.c ../../c-data-structures/src/dynamic_vector.c ../../c-data-structures/src/heap.c
TEST = ./test/sched_test.c
CPPFLAGS = -I./include/ -I../../c-data-structures/include/
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -fPIC
LDFLAGS =-L. -Wl,-install_name -lsched_utils
OBJS =  uid.o task.o heap_pq.o heap.o  sched.o dynamic_vector.o

all: $(TARGET_LIB) $(TARGET)

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -shared -o $@ $^
	
$(TARGET): $(TEST) $(TARGET_LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS)

$(OBJS): 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SOURCE) 
	
debug: CFLAGS += -g
debug: $(TARGET_LIB) $(TARGET)

release: CFLAGS += -O3
release: $(TARGET_LIB) $(TARGET)

.PHONY: update
update:
	touch $(SOURCE) $(TEST)
	
.PHONY:  clean
clean:
	rm $(OBJS) $(TARGET_LIB) $(TARGET)
