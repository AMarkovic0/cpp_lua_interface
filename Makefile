CC = g++
TARGET = main
MAINFILE_TEST = ./examples/test.cpp

SRCDIR = ./src/
INCDIRS = /usr/include/lua5.1 ./inc/
LIBDIRS = /usr/bin/

SRCFILES = luaclass.cpp luahelper.cpp
SRCFILES_TEST = luaclass.cpp luahelper.cpp

SRC = ./$(MAINFILE) $(addprefix $(SRCDIR), $(SRCFILES))
SRC_TEST = ./$(MAINFILE_TEST) $(addprefix $(SRCDIR), $(SRCFILES_TEST))
INC = $(addprefix -I, $(INCDIRS))
LIB = $(addprefix -L, $(LIBDIRS))
LINK = -llua5.1

CFLAGS = $(LIB) $(INC) $(LINK)

all:
	$(CC) -o $(TARGET) $(SRC_TEST) $(CFLAGS)

run:
	./$(TARGET)

clean:
	rm ./$(TARGET)

