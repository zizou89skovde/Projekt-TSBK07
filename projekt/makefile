IDIR=include
CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -Wall -g -DGL_GLEXT_PROTOTYPES
ODIR=obj
LIBS=-lGL -lglut -lm 
DEPS=include/GL_utilities.c include/VectorUtils3.c include/loadobj.c include/LoadTGA.c include/MicroGlut.c

all: main

main: 
	@echo $(MAKECMDGOALS) #$(CC) $(CFLAGS) $(LIBS) $(DEPS) -DVERBOSE=1 -o parachute ui.c camera.c main.c graphics.c textures.c shaders.c


clean :
	rm -rf *o parachute	
