#ifndef GLOBALS_H
#define GLOBALS_H

// Enum for game states
enum GameState {
	MAIN_MENU_STATE,
	FLYING_STATE,
	DEAD_STATE
};

extern unsigned int g_ticks;
extern GameState g_currentState;

#endif
