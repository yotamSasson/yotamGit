TARGET = a.out
CC = gcc
SOURCE = ./src/uid.c
TEST = ./test/uid_test.c
CPPFLAGS = -I./include/
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
OBJS = uid_test.o uid.o

all: $(TARGET)

$(TARGET): 	$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SOURCE)  $(TEST)
	

debug: CFLAGS += -g
debug: $(TARGET)

release: CFLAGS += -O3
release: $(TARGET)

.PHONY: update
update:
	touch $(SOURCE) $(TEST)
	
.PHONY:  clean
clean:
	rm $(OBJS) $(TARGET)
