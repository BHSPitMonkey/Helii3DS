/*
 *      SmokeTrail.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class header for SmokeTrail objects.
 */

#include <3ds.h>
#include "Drawing.h"

#ifndef SMOKETRL_H
#define SMOKETRL_H

#define NUM_CLOUDS 5

class SmokeTrail {

public:

	// Constructors and destructor
	SmokeTrail();						// default constructor
	~SmokeTrail();						// destructor

	// Initializer
	void resetAll();		// All columns to starting positions!

	// Operations
	void update();	// Recalculate positions
	void Draw();	// Draw the columns to the screen

protected:

	// Drawing objects
	//Image smokeImage;
	Sprite clouds[NUM_CLOUDS];

	unsigned short int first;
};

#endif
