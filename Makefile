CC = g++
TARGET = main
LIB_TARGET = libluainterface.a
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

.PHONY: clean run

all:
	$(CC) -o $(TARGET) $(SRC_TEST) $(CFLAGS)

run:
	./$(TARGET)

clean:
	rm -f ./*.o
	rm -f ./*.a
	rm -f ./$(TARGET)

lib:
	$(CC) -c $(addprefix $(SRCDIR), $(SRCFILES)) $(CFLAGS)
	ar rvs $(LIB_TARGET) *.o
	rm ./*.o
