################################################################
#
# $Id:$
#
# $Log:$
#
CC=  g++  # gcc or g++

CFLAGS=-g -Wall -m32 -lpam # -DUSEASM 

# subdirectory for objects
O=./build
S=./src

# not too sophisticated dependency
OBJS=				\
		$(O)/login.o

all:	 $(O)/bj

clean:
	rm -f ./build/*.o

run: all
	$(O)/bj

$(O)/bj:	$(OBJS) $(O)/main.o
	$(CC) $(CFLAGS) $(OBJS) $(O)/main.o \
	-o $(O)/bj $(LIBS)

$(O)/%.o:	$(S)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

#############################################################
#
#############################################################
