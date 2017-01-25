TARGET = waternetworks

GEO_PATH = ./geosteiner
LP_PATH = ./lp_solve
GEOLIB = $(GEO_PATH)/memory.o -L${GEO_PATH} -lgeosteiner $(LP_PATH)/libLPS.a

EPA_PATH = ./epanet
EPALIB = $(EPA_PATH)/libtoolkit.a

all: $(TARGET).c randompoints
	gcc -o $(TARGET) $(TARGET).c $(GEOLIB) $(EPALIB) -lm
	
randompoints: randompoints.c
	gcc -o randompoints randompoints.c $(GEOLIB) -lm

clean:
	rm $(TARGET)
	
