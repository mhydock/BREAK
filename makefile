SOURCES = runGame.c displayGame.c managePlayer.c setUpGrid.c inputMethods.c collisionCheck.c
OBJECTS = runGame.o displayGame.o managePlayer.o setUpGrid.o inputMethods.o collisionCheck.o
HEADERS = runGame.h

CC = gcc
CFLAGS = -g -Wall

linux: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lm -lGL -lGLU -lglut -lX11 -o project2

mac: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lm -framework GLUT -framework OpenGL -o project2
clean:
	rm -fR *o
