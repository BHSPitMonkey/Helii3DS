/*
 *      Column.cpp
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include "Drawing.h"
#include "Column.h"
#include "CaveManager.h"
#include "Player.h"

extern Player thePlayer;

// Default constructor
Column::Column()
{
	// Column width and height
	theRect.width = COL_WIDTH - 1;	// Equal column width (+1 to seal gaps)
	theRect.height = 100;			// gets randomized when spawned

	// Set up column appearance
	theQuad.SetFillColor(0, 255, 0);	// Green fill!
//	theQuad.SetBorder(true);
//	theQuad.SetBorderWidth(2);
//	theQuad.SetBorderColor((GXColor){ 0, 0, 0, 255 });	// Black border!
}

// Destructor
Column::~Column() { }

void Column::spawn(bool isGround)
{
	// Spawn the column at the right edge of the screen
	spawn(isGround, 400 + MARGIN - 1);
}

void Column::spawn(bool isGround, float x)
{
	// Randomize the height TODO (currently using bad random generator)
	srand((unsigned)time(0));	// Seed the random number generator using the X position

	spawn(isGround, x, 25 + rand()%50);
}

void Column::spawn(bool isGround, float x, int height)
{
	// Save the x coordinate we were given
	x_pos = x;

	// Save the height we were given
	theRect.height = height;

	// If this is to be a floor column, place at bottom. Else top.
	if (isGround)
		y_pos = 240 - theRect.height;
	else
		y_pos = 0;	
}

void Column::spawnObstacle(float x, float y, float height) {

	// Save the x coordinate we were given
	x_pos = x;

	// Save the x coordinate we were given
	y_pos = y;

	// Save the height we were given
	theRect.height = height;		
}

Rectangle Column::getRect() {
	return theRect;
}

float Column::getXpos() {
	return x_pos;
}

// Returns true if this column collides with the player
bool Column::CollidesWithPlayer() {
	return thePlayer.CollidesWith(theRect);
}

// Push the column left
void Column::pushLeft(float amount)
{
	x_pos -= amount;	
}

void Column::Draw()
{
    // Bounds check
    if (x_pos < 0 || x_pos >= 400) {
        return;
    }

	// Redefine the drawing rectangle according to mover position.
	theRect.x = (int)x_pos;
	theRect.y = (int)y_pos;
	theQuad.SetRectangle(theRect);
	
	/* Temporary: Turn column red if player is touching.
	if (CollidesWithPlayer())
		theQuad.SetFillColor((GXColor){ 255, 0, 0, 255 });
	else
		theQuad.SetFillColor((GXColor){ 0, 255, 0, 255 });
	*/

	// Draw the Quad
	theQuad.Draw();
}
