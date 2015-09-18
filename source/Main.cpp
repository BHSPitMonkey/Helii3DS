#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <sftd.h>
#include <sf2d.h> // Move to Drawing
#include "globals.h"
#include "Player.h"
#include "CaveManager.h"
#include "Drawing.h"
#include "knewave_ttf.h"

// Global variables
unsigned int g_ticks = 0;			// Counts how many frames we've drawn, period
unsigned int g_gameTime = 0;			// Counts how many frames have passed in current game
unsigned int g_currentStateTime = 0;	// Counts how many frames have passed in current state
GameState g_currentState;			// Decides what state or mode the game is in
Player thePlayer;
CaveManager theCave;
unsigned int g_highScore = 0;

// Colors
u32 white = RGBA8(255, 255, 255, 255);
u32 white_80 = RGBA8(255, 255, 255, (int)(255*.8));

unsigned int getScore()
{
    return g_gameTime / 10;
}

void setGameState(GameState newState)
{
    // First things first
    g_currentState = newState;

    // Reset the timer
    g_currentStateTime = 0;

    // Do certain things when these changes happen
    switch (newState) {
        // When changing to the Main Menu state
        case MAIN_MENU_STATE:
                // Respawn the player and the cave
                thePlayer.spawn();
                theCave.resetAll();

                // Update the player and the cave once, just to get their starting appearances right.
                theCave.update();		// Update the position of the cave
                thePlayer.Move();		// Reposition the player
        break;

        // When changing to the Flying state
        case FLYING_STATE:
                g_gameTime = 0;
        break;

        // When changing to the Dead state
        case DEAD_STATE:
            thePlayer.die();
            printf("You died! Your distance was: %d\n", getScore());
        break;
    }
}

int main()
{
	Drawing::Init();
    Drawing::SetClearColor(0x24, 0x1E, 0x0E);  // Brown
    
    // Font loading
	sftd_init();
	sftd_font *font = sftd_load_font_mem(knewave_ttf, knewave_ttf_size);
    char currentScoreString[7];
    char highScoreString[7];

    //Initialize console on lower screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	//consoleInit(GFX_BOTTOM, NULL);
    printf("Helii!\n\n");
    printf("Ported with love by BHSPitMonkey.\n\n");
    printf("Press A to fly or reset.\n");
    printf("Press START to pause.\n");
    printf("Press X or SELECT to exit.\n\n");
    
    thePlayer.Init();

	// Go into the main menu state
	setGameState(MAIN_MENU_STATE);
    
	bool paused = false;

	while (aptMainLoop())
	{        
        // Scan for input
        hidScanInput();
		u32 kDown = hidKeysDown();
		//u32 kUp = hidKeysUp();
        u32 kHeld = hidKeysHeld();

        // Quit the game (break out of the runloop) if HOME is pressed
		if ((kDown & KEY_X) || (kDown & KEY_SELECT))
		{
            break;
        }
        
        // Start drawing top frame elements
        Drawing::StartTopLeftFrame();

        // Do different things depending on the game state.
		switch (g_currentState) {
			
			case MAIN_MENU_STATE:
				// When A is pressed, start the game's flying mode
				if (kDown & KEY_A) {
					setGameState(FLYING_STATE);
				}

				// Draw everything
				theCave.Draw();			// Draw the cave
				thePlayer.Draw();		// Draw the player
			
			break;
			
			case FLYING_STATE:

                // When A is held (and game is not paused), fly the plane.
                if ((kHeld & KEY_A) && !paused) {
                    thePlayer.thrust();
                }

                // When + is pressed, pause or unpause.
                if (kDown & KEY_START)
                    paused = !paused;

                // If the player touches the cave, you die.
                if (theCave.CollidesWithPlayer()) {
                    setGameState(DEAD_STATE);
                }
                
                // If the player goes off screen (shouldn't be possible), you die.
                if (thePlayer.GetY() < -MARGIN || thePlayer.GetY() > 240 + MARGIN) {
                    setGameState(DEAD_STATE);
                }

                // Move everything (unless paused)
                if (!paused) {
                    theCave.update();		// Update the position of the cave
                    thePlayer.Move();		// Reposition the player
                }

                // Draw everything
                theCave.Draw();			// Draw the cave
                thePlayer.Draw();		// Draw the player

                // Increment the game timer
                g_gameTime++;

			break;
			
			case DEAD_STATE:

				// When + is pressed, reset back to main menu
				if(kDown & KEY_A) {
					setGameState(MAIN_MENU_STATE);
				}
				
				// Draw everything
				theCave.Draw();			// Draw the cave
				thePlayer.Draw();		// Draw the player
			
			break;			
		}
        
        Drawing::EndFrame();
        
        // Start drawing the bottom screen
        sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

		sftd_draw_text(font, 120, 45, white, 40, "Helii");
		sftd_draw_text(font, 100, 88, white_80, 12, "by BHSPitMonkey");
		sftd_draw_text(font, 80, 120, white, 22, "A to fly or reset");
		sftd_draw_text(font, 80, 148, white, 22, "START to pause");
		sftd_draw_text(font, 80, 176, white, 22, "SELECT to exit");
        
        // Draw the score
        unsigned int score = getScore();
        snprintf(currentScoreString, 7, "%06d", score);
        sftd_draw_text(font, 251, 4, white, 14, currentScoreString);
        if (score > g_highScore) {
            g_highScore = score;
        }
        snprintf(highScoreString, 7, "%06d", g_highScore);
        sftd_draw_text(font, 251, 18, white, 14, highScoreString);

        // Done drawing the bottom screen
		sf2d_end_frame();
        
        g_ticks++;
        g_currentStateTime++;

        Drawing::SwapBuffers();
   	}

	Drawing::Finish();
	return 0;
}
