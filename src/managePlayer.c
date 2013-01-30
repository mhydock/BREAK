//=============================================================================
// Programmer:		Matthew Hydock
// Professor:		Dr. Mooney
//
// File name:		userMethods.c
// File description:	A collection of methods to modify user variables
//			(movable parts) and game-state variables (difficulty,
//			lives, score, etc).
//=============================================================================

#include "runGame.h"

void correctPaddle()
// Method to correct the paddle's current position, to make sure it is within
// the play arena.
{	
	if (paddlePos < 1)
		paddlePos = 1;
	if (paddlePos > 57)
		paddlePos = 57;
	
	if (!gameStart)
	{
		ball.x = paddlePos + 7;
		ball.y = 6;
		ball.velH = 0;
		ball.velV = 0;
	}

}

void updateBall()
// Updates the ball's current position based on the ball's current vertical and
// horizontal velocities.
{
	ball.x += ball.velH;
	ball.y += ball.velV;
}

void startRound()
// Sets the gameStart and the ball's velocity.
{
	gameStart = 1;
	ball.velH = .1;
	ball.velV = .1;
}

void restartRound(int i)
// Resets the ball's position and velocity, and decrements the amount of lives
// according to a user-defined value. This allows it to be used in the case of
// missing the ball and/or winning a round.
{
	lives -= i;
	gameStart = 0;
	ball.x = paddlePos + 7;
	ball.y = 6;
	ball.velH = 0;
	ball.velV = 0;
}

void setGame()
// Sets up the game under the base settings, including the position of the ball
// and paddle, as well as the score and starting lives.
{
	playGame = 0;
	gameStart = 0;
	difficulty = 10;
	score = 0;
	lives = 3;

	paddlePos = 28;
	ball.x = 35;
	ball.y = 6;
	ball.velH = 0;
	ball.velV = 0;
	
	setUpGrid();

	struct timeval time;
	gettimeofday(&time, NULL);
	oldTime = time.tv_sec + (time.tv_usec/1000000);
}

void difficultyMenu(int i)
// Processes the difficulty menu, and changes the game's difficulty level by
// making updates occur faster/slower, and by allowing less/more lives at start.
{
	if (i == 1)
	{
		difficulty = 1;
		lives = 4;
	}

	else if (i == 2)
	{
		difficulty = 10;
		lives = 3;
	}

	else
	{
		difficulty = 100;
		lives = 2;
	}

	glutDetachMenu(GLUT_LEFT_BUTTON);
}
