//=============================================================================
// Programmer:		Matthew Hydock
// Professor:		Dr. Mooney
//
// File name:		collisionCheck.c
// File description:	Collision detection system for a breakout-type game.
//=============================================================================

#include "runGame.h"

void collisionCheck()
{
	// Find the ball's next position, and add offset for edge of ball.
	float newX = ball.x + ball.velH;
	float newY = ball.y + ball.velV;
	
	// Check each point around the ball's next position.
	int i;
	for (i = 0; i < 360; i += 18)
	{
		float tempX = newX + cos(i*180/M_PI);
		float tempY = newY + sin(i*180/M_PI);

		// Find the row and column the ball intersects (literals are graphics offsets).
		int col = (tempX-1)/BLOCK_WIDTH;
		int row = (58-tempY)/BLOCK_HEIGHT;

		// Check to see if this point is within the block grid.
		if (col >= 0 && col < 10 && row >= 0 && row < 6)
		{
			// If that particular brick still exists...
			if (blockGrid[row][col].hits > 0)
			{
				// If ball comes from left or right, reverse velH.
				if (tempX > (col+1)*BLOCK_WIDTH+1 || tempX < col*BLOCK_WIDTH+1)
					ball.velH = -ball.velH;
				
				// If ball comes from above or below, reverse velV.
				if (tempY <= 58-row*BLOCK_HEIGHT || tempY >= 58-(row+1)*BLOCK_HEIGHT)
					ball.velV = -ball.velV;

				// Remove a hit from the block, and increment score.
				blockGrid[row][col].hits--;
				blocksLeft--;
				score += 100;
			}
		}
	}

	// Adjust newX and newY so as to make detection of walls and paddle simpler.
	newX++;
	newY++;

	if (ball.velH < 0)
		newX -= 2;
		
	if (ball.velV < 0)
		newY -= 2;
		
		
	// Check to see if ball will collide with the walls or the paddle.
	if (((int)newX) == 0 || ((int)newX) == 71)
		ball.velH = -ball.velH;
		
	if (((int)newY) == 63)
		ball.velV = -ball.velV;

	if (((int)newY) == 0)
		restartRound(1);
		
	if (((int)newY) == 4 && newX >= paddlePos && newX <= paddlePos+14)
		ball.velV = -ball.velV;	
}
