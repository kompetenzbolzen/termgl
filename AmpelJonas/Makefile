CC      = /usr/bin/g++
CFLAGS  = -Wall -g
LDFLAGS = -lm -lpthread

OBJ = main.o cCar.o cCrossroad.o cObject.o cObjectHandler.o cPeasant.o cPeasantTrafficLight.o cRender.o cTrafficLight.o 

prog: $(OBJ)
	$(CC) $(CFLAGS) -o prog $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
