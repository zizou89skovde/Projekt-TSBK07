
all : parachute

lab4-3: main.c graphics.c ui.c physics.c  GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut.c
	gcc -Wall -g -std=c99 -o parachute -DGL_GLEXT_PROTOTYPES lab4-3.c GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut.c  -lGL -lglut -lm

clean :
	rm lab4-1
	
