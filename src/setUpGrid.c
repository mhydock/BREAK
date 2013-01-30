//=============================================================================
// Programmer:		Matthew Hydock
// Professor:		Dr. Mooney
//
// File name:		setUpGrid.c
// File description:	A single method to set the block grid. Reads in a file,
//			and fills in a matrix.
//=============================================================================

#include "runGame.h"

void setUpGrid()
{
	blocksLeft = 60;

	int i, j;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 10; j++)
		{
			float k = (float)j/10.0;
			blockGrid[i][j].hits = 1;
			blockGrid[i][j].r = 1 - k;
			blockGrid[i][j].g = (-4*k*k) + (4*k);
			blockGrid[i][j].b = k;
		}
}

