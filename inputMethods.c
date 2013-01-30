//=============================================================================
// Programmer:		Matthew Hydock
// Professor:		Dr. Mooney
//
// File name:		inputMethods.c
// File description:	Various methods to control user input.
//=============================================================================

#include "runGame.h"

void normalKeys(unsigned char key, int x, int y)
// Key input for normal keys.
//
// Space = start round (release ball)
// ESC   = exit game (boss button)
{
	if (key == 32 && playGame)
		startRound();
	else if (key == 27)
		exit(0);
}

void mouseClick(int button, int state, int x, int y)
// Checks to see if the mouse has been clicked.
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		GLint viewport[4];
		GLubyte pixel[3];

		glGetIntegerv(GL_VIEWPORT,viewport);

		glReadBuffer(GL_BACK);
		glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);

		if (pixel[0] == 0)
		{
			// If difficulty button has been seleted, display menu.
			if (pixel[1] == 0 && pixel[2] == 255 && !playGame)
				glutAttachMenu(GLUT_LEFT_BUTTON);

			else if (pixel[1] == 255)
			{
				// If start button has been seleted, start the game.
				if (pixel[2] == 0 && !gameStart)
					playGame = 1;

				// Otherwise, the pause button has been selected,
				// so toggle the game activation.
				else if (pixel[2] == 255)
				{
					if (!playGame)
						playGame = 1;
					else
						playGame = 0;
				}
			}
		}

		
		else if (pixel[0] == 255)
		{
			if (pixel[1] == 0)
			{
				// If game is active and arena has been clicked, then
				// start the round.
				if (pixel[2] == 0 && playGame && !gameStart)
					startRound();

				// Otherwise, the instructions button has been selected.
				// clicking it toggles the appearance of the instructions,
				// but only if gameplay hasn't begun.
				else if (pixel[2] == 255 && !playGame)
				{
					if (!instructionsOn)
						instructionsOn = 1;
					else
						instructionsOn = 0;
				}
			}
			// The only other button left is the exit button.
			else if (pixel[1] == 255)
				exit(0);
		}
	}

}

void mouseMove(int x, int y)
// Checks to see if the mouse was moved.
{
	if (playGame)
	{
		paddlePos = (float)x * (96.0/(float)glutGet(GLUT_WINDOW_WIDTH))-7;
		// Move bar to mouse position.

		correctPaddle();
		// Contains position correction code.
	}
}
