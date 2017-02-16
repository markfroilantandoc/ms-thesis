OBJECT_PATH = obj
SOURCE_PATH = src
EPANET_PATH = ./ext/epanet
GEOSTEINER_PATH = ./ext/geosteiner
LP_PATH = ./ext/lp_solve

OBJS = $(OBJECT_PATH)/main.o $(OBJECT_PATH)/geosteinerWrapper.o $(OBJECT_PATH)/epanetWrapper.o $(OBJECT_PATH)/mathUtil.o
CC = gcc
DEBUG = -g
CFLAGS = -c
EPANET_LINK = $(EPANET_PATH)/libtoolkit.a
GEOSTEINER_LINK = $(GEOSTEINER_PATH)/memory.o -L$(GEOSTEINER_PATH) -lgeosteiner
LP_LINK = $(LP_PATH)/libLPS.a
LFLAGS =  $(EPANET_LINK) $(GEOSTEINER_LINK) $(LP_LINK) -lm -o waternetworks

all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS)

$(OBJECT_PATH)/main.o: $(SOURCE_PATH)/main.c $(SOURCE_PATH)/main.h
	$(CC) $(CFLAGS) -o $(OBJECT_PATH)/main.o $(SOURCE_PATH)/main.c

$(OBJECT_PATH)/geosteinerWrapper.o: $(SOURCE_PATH)/geosteinerWrapper.c $(SOURCE_PATH)/geosteinerWrapper.h
	$(CC) $(CFLAGS) -o $(OBJECT_PATH)/geosteinerWrapper.o $(SOURCE_PATH)/geosteinerWrapper.c

$(OBJECT_PATH)/epanetWrapper.o: $(SOURCE_PATH)/epanetWrapper.c $(SOURCE_PATH)/epanetWrapper.h
	$(CC) $(CFLAGS) -o $(OBJECT_PATH)/epanetWrapper.o $(SOURCE_PATH)/epanetWrapper.c

$(OBJECT_PATH)/mathUtil.o: $(SOURCE_PATH)/mathUtil.c $(SOURCE_PATH)/mathUtil.h
	$(CC) $(CFLAGS) -o $(OBJECT_PATH)/mathUtil.o $(SOURCE_PATH)/mathUtil.c

clean:
	rm $(OBJECT_PATH)/* waternetworks
