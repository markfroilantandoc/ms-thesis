OBJECT_PATH = obj
SOURCE_PATH = src
EPANET_PATH = ext/epanet
GEOSTEINER_PATH = ext/geosteiner
LP_PATH = ext/lp_solve

OBJS = $(OBJECT_PATH)/main.o
CC = gcc
DEBUG = -g
CFLAGS = -c -Iext
LFLAGS = $(EPANET_PATH)/libtoolkit.a -lm -o waternetworks

all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS)

$(OBJECT_PATH)/main.o: $(SOURCE_PATH)/main.c $(SOURCE_PATH)/main.h
	$(CC) $(CFLAGS) -o $(OBJECT_PATH)/main.o $(SOURCE_PATH)/main.c

clean:
	rm $(OBJECT_PATH)/* waternetworks
