/*
 *      SmokeTrail.h
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class implementation for SmokeTrail objects.
 */

#include <iostream>
#include <fstream>
#include <math.h>
#include "CaveManager.h"
#include "Player.h"
//#include "smoke.h"
#include "SmokeTrail.h"

extern std::ofstream logFile;
extern unsigned int g_gameTime;
extern Player thePlayer;

// Default constructor
SmokeTrail::SmokeTrail() { 

	// Set up the sprite and texture
	//smokeImage.LoadImage(smoke, IMG_LOAD_TYPE_BUFFER);

	for (int i=0; i<NUM_CLOUDS; i++) {
		//clouds[i].SetImage(&smokeImage);
		//clouds[i].SetRotation((180.0/NUM_CLOUDS) * i);
        clouds[i].SetWidth(10);
        clouds[i].SetWidth(10);
        clouds[i].SetPlaceholderColor(100, 100, 100);
	}

	// Initially, first is the first index in the array.
	first = 0;
}

// Destructor
SmokeTrail::~SmokeTrail() { }

// Reset all clouds
void SmokeTrail::resetAll() {

	float x = -MARGIN;

	for (int i=0; i<NUM_CLOUDS; i++) {
		clouds[i].SetPosition(x + (((120.0+MARGIN)/NUM_CLOUDS) * i), 240);
		clouds[i].SetVisible(false);	
	}
	
	first = 0;
}

// Shift and update the cave manager.
void SmokeTrail::update() {

	// Push all clouds left and lower their opacity
	for (int i=0; i<NUM_CLOUDS; i++) {
		clouds[i].Move(-CAVE_SPEED, 0);
		//clouds[i].SetTransparency( clouds[i].GetTransparency() * 0.95 );
	}

	// If the first cloud is too far off-screen, reuse it
	if (clouds[first].GetX() <= -MARGIN - 1) {

		// Move the first cloud to where the player is
		clouds[first].SetPosition(120+10, thePlayer.GetY()+10);
		clouds[first].SetVisible(true);
		//clouds[first].SetTransparency(0xFF);	// Fully opaque

		first = (first+1) % NUM_CLOUDS;	// Change the index of the first column
	}	
}

void SmokeTrail::Draw() {

	// Draw all the clouds
	for (int i=0; i<NUM_CLOUDS; i++) {
		clouds[i].Draw();
	}
}
