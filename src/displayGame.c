//=============================================================================
// Programmer:		Matthew Hydock
// Professor:		Dr. Mooney
//
// File name:		displayGame.c
// File description:	A series of OpenGL commands to display
//			all of the game entities.
//=============================================================================

#include "runGame.h"

//=============================================================================
// Generic objects that are duplicated.
//=============================================================================
void drawText(char *input, int x, int y, void *font)
// Draws text, such as the score, or remaining lives.
{
	glRasterPos2i(x,y);

	int i;
	for (i = 0; i < strlen(input); i++)
	{
		glutBitmapCharacter(font, input[i]);
	}
}

void drawBlock(float r, float g, float b)
// Draws a block with the given color, with a gradient.
{
	glBegin(GL_QUADS);
		glColor3f(r,g,b);
		glVertex2d(0,-3);
		glColor3f(r/2,g/2,b/2);
		glVertex2d(0,0);
		glVertex2d(7,0);
		glColor3f(r,g,b);
		glVertex2d(7,-3);
	glEnd();
}

void drawCommandButton(int x, int y, char *str)
// Draws a blue block with a gradient, with text in the middle.
{
	glBegin(GL_QUADS);
		glColor3f(.5,.5,1.0);
		glVertex2d(x,y);
		glColor3f(0.0,0.0,.90);
		glVertex2d(x,y-3);
		glVertex2d(x+20,y-3);
		glColor3f(.5,.5,1.0);
		glVertex2d(x+20,y);

		glColor3f(0.0,0.0,.90);
		glVertex2d(x,y-3);
		glColor3f(.5,.5,1.0);
		glVertex2d(x,y-6);
		glVertex2d(x+20,y-6);
		glColor3f(0.0,0.0,.90);
		glVertex2d(x+20,y-3);
	glEnd();

	glColor3f(0.0,0.0,0.0);
	drawText(str,x+1,y-3.5,GLUT_BITMAP_HELVETICA_18);
}
//=============================================================================


//=============================================================================
// Draw player objects.
//=============================================================================
void drawPaddle()
// Draws the players movable paddle.
{
	glBegin(GL_QUADS);
		glColor3f(.75,0.0,0.0);
		glVertex2d(paddlePos,5);
		glColor3f(1.0,.5,.5);
		glVertex2d(paddlePos,4);
		glVertex2d(paddlePos+14,4);
		glColor3f(.75,0.0,0.0);
		glVertex2d(paddlePos+14,5);
	glEnd();
}

void drawBall(float x, float y)
// Draw a little red ball (both at player object and life indicator).
{
	float j;				// floating point number to hold
						// the current angle as a radian.

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0,0.0,0.0);

		int i;
		for (i = 0; i != 360; i++)
		// Draws a triangle each loop, forming a smooth arc.
		{
			glVertex2i(x,y);

			j = (float)i * M_PI/180;
			glVertex2d((cos(j)*1.0)+x, (sin(j)*1.0)+y);

			j = ((float)i+1) * M_PI/180;
			glVertex2d((cos(j)*1.0)+x, (sin(j)*1.0)+y);
		}
		
	glEnd();

}
//=============================================================================


//=============================================================================
// Draw game environment.
//=============================================================================
void drawGrid()
// Draw the block grid.
{
	int i, j;
	glTranslatef(1.0,58.0,0.0);
	for (i = 0; i < 6; i++)
	{
		glPushMatrix();
		for (j = 0; j < 10; j++)
		{
			if (blockGrid[i][j].hits > 0)
				drawBlock(blockGrid[i][j].r,blockGrid[i][j].g,blockGrid[i][j].b);

			glTranslatef(7.0,0.0,0.0);
		}
		glPopMatrix();
		glTranslatef(0.0,-3.0,0.0);
	}
}

void drawArena()
// Display the arena and score boxes.
{
	glColor3f(1.0,1.0,1.0);

	glPolygonMode(GL_FRONT, GL_LINE);

	glBegin(GL_QUADS);
		glVertex2d(1,1);
		glVertex2d(71,1);
		glVertex2d(71,63);
		glVertex2d(1,63);
	glEnd();

	glBegin(GL_QUADS);
		glVertex2d(73,1);
		glVertex2d(95,1);
		glVertex2d(95,63);
		glVertex2d(73,63);
	glEnd();
}

void drawInstructions()
// Draws the game's instructions to the screen in a large box.
{
	glBegin(GL_QUADS);
		glColor3f(.5,.5,1.0);
		glVertex2d(1,1);
		glVertex2d(71,1);
		glVertex2d(71,63);
		glVertex2d(1,63);
	
		glColor3f(0.0,0.0,0.9);
		glVertex2d(2,2);
		glVertex2d(70,2);
		glVertex2d(70,62);
		glVertex2d(2,62);
	glEnd();

	glColor3f(1.0,1.0,1.0);

	drawText("INSTRUCTIONS",27,55,GLUT_BITMAP_HELVETICA_18);
	drawText("BREAK ALL OF THE BLOCKS TO ADVANCE TO THE NEXT LEVEL",3,50,GLUT_BITMAP_HELVETICA_12);
	drawText("BOUNCE BALL WITH PADDLE TO BREAK THE BLOCKS",3,45,GLUT_BITMAP_HELVETICA_12);
	drawText("IF THE BALL HITS THE FLOOR, YOU LOSE A LIFE; NO LIVES, GAME OVER",3,40,GLUT_BITMAP_HELVETICA_12);
	drawText("MOVE PADDLE WITH MOUSE, RELEASE BALL WITH LEFT CLICK OR SPACEBAR",3,35,GLUT_BITMAP_HELVETICA_12);
	drawText("TO QUIT GAME, PRESS \"ESC\" OR CLICK \"EXIT\"",3,30,GLUT_BITMAP_HELVETICA_12);
	drawText("GAME CAN BE PAUSED AT ANY TIME BY CLICKING \"PAUSE\"",3,25,GLUT_BITMAP_HELVETICA_12);
	drawText("DIFFICULTY CAN BE CHANGED ONLY BEFORE GAMEPLAY BEGINS",3,20,GLUT_BITMAP_HELVETICA_12);
	drawText("--CLICK \"INSTRUCTIONS\" TO RETURN TO BEGINNING SCREEN--",11.5,10,GLUT_BITMAP_HELVETICA_12);
}
//=============================================================================


//=============================================================================
// Main display methods.
//=============================================================================
void displayGame()
{
	// Turn the score into a string, for output to screen.
	char scoreBuf[6];
	sprintf(scoreBuf, "%d", score);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);

	// If the instructions aren't being displayed, draw arena.
	if (!instructionsOn)
	{
		// Draw contents of arena.
		glPushMatrix();
		drawGrid();

		glPopMatrix();
		drawPaddle();
		drawBall(ball.x, ball.y);
	}
	// Else, draw the instructions window.
	else
		drawInstructions();

	// Draw contents of score box.
	glColor3f(1.0,1.0,1.0);
	drawText("SCORE",74,56, GLUT_BITMAP_HELVETICA_18);
	drawText("LIVES",74,45, GLUT_BITMAP_HELVETICA_18);

	int i;
	for (i = 0; i < lives; i++)
		drawBall(75 + (i * 3), 43);

	glColor3f(1.0,0.0,0.0);
	drawText(scoreBuf,74, 53, GLUT_BITMAP_HELVETICA_18);

	// Draw border for buttons.
	glColor3f(0.0,0.0,0.5);
	glBegin(GL_QUADS);
		glVertex2d(95,37);
		glVertex2d(73,37);
		glVertex2d(73,1);
		glVertex2d(95,1);
	glEnd();

	// Draw buttons.
	drawCommandButton(74,36,"START");
	drawCommandButton(74,29,"DIFFICULTY");
	drawCommandButton(74,22,"INSTRUCTIONS");
	drawCommandButton(74,15,"PAUSE");
	drawCommandButton(74,8,"EXIT");

	drawArena();
}

void drawPickables()
// Draws the colored boundaries for all of the pickable objects.
{
	glPolygonMode(GL_FRONT, GL_FILL);

	if (!instructionsOn)
	{
		// Draw arena box
		glColor3ub(255,0,0);
		glBegin(GL_QUADS);
			glVertex2d(1,1);
			glVertex2d(71,1);
			glVertex2d(71,63);
			glVertex2d(1,63);
		glEnd();

		// Draw start button.
		glColor3ub(0,255,0);
		glBegin(GL_QUADS);
			glVertex2d(74,36);
			glVertex2d(74,30);
			glVertex2d(94,30);
			glVertex2d(94,36);
		glEnd();

		// Draw difficulty button.
		glColor3ub(0,0,255);
		glBegin(GL_QUADS);
			glVertex2d(74,29);
			glVertex2d(74,23);
			glVertex2d(94,23);
			glVertex2d(94,29);
		glEnd();

		// Draw pause button.
		glColor3ub(0,255,255);
		glBegin(GL_QUADS);
			glVertex2d(74,15);
			glVertex2d(74,9);
			glVertex2d(94,9);
			glVertex2d(94,15);
		glEnd();

		// Draw exit button.
		glColor3ub(255,255,0);
		glBegin(GL_QUADS);
			glVertex2d(74,8);
			glVertex2d(74,2);
			glVertex2d(94,2);
			glVertex2d(94,8);
		glEnd();
	}

	// Draw instructions button.
	glColor3ub(255,0,255);
	glBegin(GL_QUADS);
		glVertex2d(74,22);
		glVertex2d(74,16);
		glVertex2d(94,16);
		glVertex2d(94,22);
	glEnd();
}

//=============================================================================
