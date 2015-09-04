/*
 *      Player.cpp
 *      
 *      Copyright 2009 Stephen Eisenhauer <mail@stepheneisenhauer.com>
 * 
 * 		Class for Player objects.
 */

#include "Drawing.h"
#include "Player.h"
#include "globals.h"

void Player::Init() { 

	// Set up the heli sprite and texture
    heliImage.LoadImage("/3ds/Helii3DS/img/heli.png");
	heliSprite.SetImage(&heliImage);
	heliSprite.SetX(120);
//	heliSprite.DefineCollisionRectangle(3, 17, 47, 29);

    // Obviated by SetImage now
    //sf2d_texture * tex = heliImage.GetTexture();
    //heliSprite.SetWidth(tex->width);
    //heliSprite.SetHeight(tex->height);

	// Set up the fire sprite and texture
	fireImageSheet.LoadImage("/3ds/Helii3DS/img/fire.png");
	fireSprite.SetImage(&fireImageSheet, 64, 64);
	fireSprite.SetX(120);

    theSmokeTrail.Init();

	// Set default physical state
	spawn();
}

// Destructor
Player::~Player() { }

// Initializer
void Player::spawn() {

	// Reset the smoke trail
	theSmokeTrail.resetAll();

	// Starting position for a Player
	y_coord = 120;

	// Reset Player velocity to 0
	y_veloc = -50;

    // Reset color
    heliSprite.SetPlaceholderColor(200, 0, 0);
}

int Player::GetY() {
	return y_coord;
}

// Returns true if the helicopter is touching a given rectangle
bool Player::CollidesWith(const Rectangle rect, float x, float y) {
	return heliSprite.CollidesWith(rect, x, y);
}

// Control the player
void Player::thrust()
{
	y_veloc -= THRUST;		// Remember, the y- direction is up.
}

void Player::die()
{
    heliSprite.SetPlaceholderColor(100, 0, 0);
}

// Reposition the player for a new frame
void Player::Move()
{
	y_veloc += GRAVITATION;		// Gravity influences velocity

	// Keep the velocity within bounds
	if (y_veloc > MAX_VELOCITY)
		y_veloc = MAX_VELOCITY;
	else if (y_veloc < -MAX_VELOCITY)
		y_veloc = -MAX_VELOCITY;

	y_coord += y_veloc;		// Velocity influences position

	theSmokeTrail.update();	// Update the smoke trail
}

// Draw the player
void Player::Draw()
{
	// Draw the smoke trail
	theSmokeTrail.Draw();

	// Place the sprite where the player is
	heliSprite.SetY(y_coord);

	// Rotate the helicopter in accordance with its movement
	heliSprite.SetRotation(y_veloc);

	// Draw the heli sprite
	heliSprite.Draw();
//
//	// Draw the fire, if DEAD_STATE.
//	if (g_currentState == DEAD_STATE) {
//		fireSprite.SetY(y_coord);
//		if (g_ticks % 5 == 0)
//			fireSprite.NextFrame();
//		fireSprite.Draw();
//	}
    /*
    // FIXME: Just draw a plain rect
    rend.drawFillRect(
        100,
        y_coord,
        100 + 16,
        y_coord + 16,
        255,
        0,
        0,
        rend.topl
    ); */
}
