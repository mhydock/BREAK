//=============================================================================
// Programmer:		Matthew Hydock
// Professor:		Dr. Mooney
//
// File name:		runGame.h
// File description:	Definitions of various methods, variables
//			and structures used across the game.
//=============================================================================


//=============================================================================
// Include statments
//=============================================================================
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// standard cross-platform includes
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

// for debugging
#include <stdio.h>

// to make the collision code more universal and easier to understand.
#define BLOCK_WIDTH 7
#define BLOCK_HEIGHT 3
//=============================================================================


//=============================================================================
// Structures used to collect game data
//=============================================================================
struct Block
// Common structure for a block (game object).
{
	int hits;
	float r, g, b;
};

struct Ball
// Common structure for a ball (cleans up code).
{
	float x, y;
	float velH, velV;
};
//=============================================================================


//=============================================================================
// Global variables
//=============================================================================
int playGame;			// treated like a boolean
int gameStart;			// treated like a boolean
int instructionsOn;		// treated like a boolean
int difficulty;			// difficulty level (power of 10)

int lives;			// current lives of player
int score;			// player's score
int blocksLeft;			// amount of blocks left in level
struct Block blockGrid[6][10]; 	// array to hold block data

float paddlePos;		// horizontal position of player's paddle
struct Ball ball;		// ball's position and velocity

double oldTime;			// time of previous program loop (frame limiter)
//=============================================================================


//=============================================================================
// Game methods
//
// Note: The methods listed are used across files; there are some methods in
//	 the individual files that aren't listed here, because they are only
//	 used locally (such as methods to display specific objects).
//=============================================================================

// Fill block grid and count all blocks.
void setUpGrid();
// Found in:	setUpGrid.c

//----------------------------------------------------------------------------

// Display ALL game components (if there's an error in graphics, it'll be here).
void displayGame();
void drawPickables();
// Found in:	displayGame.c

//----------------------------------------------------------------------------

// Player object/Game state modifiers.
void correctPaddle();
void updateBall();
void startRound();
void restartRound(int i);
void setGame();
void difficultyMenu(int i);
// Found in:	managePlayer.c

//----------------------------------------------------------------------------

// Player input methods.
void normalKeys(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void mouseMove(int x, int y);
// Found in:	inputMethods.c

//----------------------------------------------------------------------------

// Detect collisions and tally score.
void collisionCheck();
// Found in:	collisionCheck.c

//=============================================================================
