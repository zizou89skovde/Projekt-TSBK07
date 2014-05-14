IDIR=include
CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -Wall -g -DGL_GLEXT_PROTOTYPES -D_POSIX_C_SOURCE=199309 
ODIR=obj
LIBS=-lGL -lglut -lm  -lrt
DEPS=include/GL_utilities.c include/VectorUtils3.c include/loadobj.c include/LoadTGA.c include/MicroGlut.c

all: main

main: 
	$(CC) $(CFLAGS) $(LIBS) $(DEPS) -o parachute ui.c camera.c main.c object.c graphics.c textures.c shaders.c terrain.c physics.c particles.c
clean :
	rm -rf *o parachute	



