CC = g++
TARGET = main
MAINFILE = test.cpp

SRCDIR = ./src/
INCDIRS = /usr/include/lua5.1 ./inc/
LIBDIRS = /usr/bin/

SRCFILES = luaclass.cpp

SRC = ./$(MAINFILE) $(addprefix $(SRCDIR), $(SRCFILES))
INC = $(addprefix -I, $(INCDIRS))
LIB = $(addprefix -L, $(LIBDIRS))
LINK = -llua5.1

CFLAGS = $(LIB) $(INC) $(LINK)

all:
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

run:
	./$(TARGET)

clean:
	rm ./$(TARGET)

