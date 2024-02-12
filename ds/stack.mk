TARGET = a.out
CC = gcc
SOURCE = ./src/stack.c
TEST = ./test/stack_test.c
CPPFLAGS = -I./include/
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
OBJS = stack.o stack_test.o

all: $(TARGET)

$(TARGET): 	$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SOURCE)  $(TEST)

	
debug: CFLAGS += -g
debug: $(TARGET)

release: CFLAGS += -O3
release: $(TARGET)

clean:
	rm $(OBJS) $(TARGET)