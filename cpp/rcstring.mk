TARGET = a.out
CC = g++
SOURCE = ./src/rcstring.cpp
TEST = ./test/rcstring_test.cpp
CPPFLAGS = -I./include/ -I/Users/yotamsasson/Documents/Git/yotamGit/utils/include/
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra 
OBJS = rcstring_test.o rcstring.o

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
