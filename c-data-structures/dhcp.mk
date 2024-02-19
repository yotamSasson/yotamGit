TARGET = a.out
CC = gcc
SOURCE = ./src/dhcp.c ./src/trie.c 
TEST = ./test/dhcp_test.c
CPPFLAGS = -I./include/ 
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
OBJS = dhcp.o dhcp_test.o trie.o 

all: $(TARGET)

$(TARGET): 	$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SOURCE)  $(TEST)
	

debug: CFLAGS += -g
debug: $(TARGET)

release: CFLAGS += -O3
release: $(TARGET)

test: CFLAGS += -O0
test: $(TARGET)

.PHONY: update
update:
	touch $(SOURCE) $(TEST)
	
.PHONY:  clean
clean:
	rm $(OBJS) $(TARGET)