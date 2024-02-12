TARGET = a.out
CC = g++
TEST = ./test/shared_pointer_test.cpp
CPPFLAGS = -I./include/ -I/Users/yotamsasson/Documents/Git/yotamGit/utils/include/
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -O0 
OBJS = shared_pointer_test.o

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
	