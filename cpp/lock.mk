TARGET = a.out
CC = g++
TEST = ./test/lock_test.cpp
CPPFLAGS = -I./include/ 
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra
OBJS = lock_test.o

all: $(TARGET)

$(TARGET): 	$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c  $(TEST) 

	
debug: CFLAGS += -g
debug: $(TARGET)

release: CFLAGS += -O3
release: $(TARGET)

clean:
	rm $(OBJS) $(TARGET)