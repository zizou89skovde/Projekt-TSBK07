
all : lab3-1

lab3-1: lab3-1.c GL_utilities.c 
	gcc -Wall -std=c99 -o lab3-1 -lGL -lm -DGL_GLEXT_PROTOTYPES lab3-1.c GL_utilities.c MicroGlut.c loadobj.c LoadTGA.c VectorUtils3.c

lab3-2: lab3-2.c GL_utilities.c 
	gcc -Wall -std=c99 -o lab3-2 -lGL -lm -DGL_GLEXT_PROTOTYPES lab3-2.c GL_utilities.c MicroGlut.c loadobj.c LoadTGA.c VectorUtils3.c

lab3-3: lab3-3.c GL_utilities.c 
	gcc -Wall -g -std=c99 -o lab3-3 -lGL -lm -DGL_GLEXT_PROTOTYPES lab3-3.c GL_utilities.c MicroGlut.c loadobj.c LoadTGA.c VectorUtils3.c

lab3-5: lab3-5.c GL_utilities.c 
	gcc -Wall -g -std=c99 -o lab3-5 -lGL -lm -DGL_GLEXT_PROTOTYPES lab3-5.c GL_utilities.c MicroGlut.c loadobj.c LoadTGA.c VectorUtils3.c


clean :
	rm lab3-1
	rm lab3-2
	rm lab3-5
