//=============================================================================
// Programmer:		Matthew Hydock
// Professor:		Dr. Mooney
//
// File name:		runGame.c
// File description:	A Breakout game in OpenGL.
//=============================================================================

#include "runGame.h"

//=============================================================================
// GL methods
//=============================================================================

void init()
// Initialize game variables and OpenGL system.
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);

	setGame();

	int menu = glutCreateMenu(difficultyMenu);
	glutAddMenuEntry("Easy", 1);
	glutAddMenuEntry("Medium", 2);
	glutAddMenuEntry("Hard", 3);
}

void display()
// Display the game graphics (blocks, paddle, ball, etc).
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,96,0,64);
	glPolygonMode(GL_FRONT, GL_FILL);

	if (lives < 0)
		setGame();

	if (playGame)
	{
		// if there are no blocks left, restart the round.
		if (!blocksLeft)
		{
			restartRound(-1);
			setUpGrid();
		}

		// if an appropriate amount of time has passed, update ball and
		// run the collision detection.
		struct timeval time;
		gettimeofday(&time, NULL);
		double newTime = time.tv_sec + (time.tv_usec/1000000.0);
		if (newTime-oldTime > .005 / difficulty)
		{
			updateBall();
			collisionCheck();
			oldTime = newTime;
		}
	}

	displayGame();
	
	glFlush();
	glutSwapBuffers();

	drawPickables();
	glFlush();
}

int main (int argc, char* argv[])
// Display window with input attachments.
{
	// set up main window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(750, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Breakout!");

	init();

	// register display methods
	glutDisplayFunc(display);
	glutIdleFunc(display);

	// register input methods
	glutKeyboardFunc(normalKeys);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);
	
	glutMainLoop();
	return 0;
}
//=============================================================================

