/*
 *      CaveManager.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class header for CaveManager objects.
 */

#include "Drawing.h"
#include "Column.h"

#ifndef CAVEMGR_H
#define CAVEMGR_H

#define CAVE_HEIGHT 240
#define NUM_COLUMNS 40
#define NUM_OBSTACLES 2
#define OBSTACLE_SPACING (int)((400.0 + (2.0 * MARGIN)) / NUM_OBSTACLES)
#define CAVE_SPEED 3
#define MARGIN 50
#define COL_WIDTH (int)((400.0 + (2.0 * MARGIN)) / NUM_COLUMNS)
#define INITIAL_CAVE_TOP 25
#define INITIAL_CAVE_SPACING 190
#define MIN_CAVE_SPACING 50
#define MAX_CAVE_TOP_CHANGE 2

class CaveManager {
private:

	friend class Column;				// TODO: Not sure this is needed

	Column roof[NUM_COLUMNS];			// Roof columns
	Column ground[NUM_COLUMNS];			// Ground columns
	Column obstacles[NUM_OBSTACLES];	// Obstacle columns

	float caveTop;			// Holds the y-coordinate for the top of the cave
	float caveSpacing;		// Holds the current height of the cave

	unsigned short first;				// Index of the first column

public:

	// Constructors and destructor
	CaveManager();			// default constructor
	~CaveManager();			// destructor

	// Initializer
	void resetAll();		// All columns to starting positions!

	bool CollidesWithPlayer();

	// Operations
	void update();	// Recalculate positions
	void Draw();	// Draw the columns to the screen

};

#endif
