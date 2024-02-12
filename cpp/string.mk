TARGET = a.out
CC = g++
SOURCE = ./src/string.cpp
TEST = ./test/string_test.cpp
CPPFLAGS = -I./include/
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra 
OBJS = string.o string_test.o

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