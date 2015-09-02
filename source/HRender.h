/**
 * 2D drawing library functions.
 */

#ifndef HRENDER_H
#define HRENDER_H
#include <3ds.h>

//-------------------------------------
//credit and much respect to Smealum && AlbertoSONIC;

class Render
{
public: 
Render();
void screenRender();
u8 *topl = 0;        // Dont have to declare screen just reference them as part of class
u8 *topr = 0;
u8 *bottom = 0;
void clearBottom();
void clearTop();
void drawChar(char letter,int x,int y, char r, char g, char b, u8* screen);
void drawString(char* word, int x,int y, char r, char g, char b, u8* screen,gfxScreen_t screenPos);
void drawLine( int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen);
void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3,char r,char g, char b,u8 *screen);
void drawRect( int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen);
void drawFillRect( int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen, bool v=0);
void drawCircle(int x, int y, int radius, char r, char g, char b, u8* screen);
void drawFillCircle(int x, int y, int radius, char r , char g, char b, u8* screen);
void drawCircleCircum(int xc, int yc, int x,int y, char r, char g, char b, u8* screen);
void clearScreen(u8* screen,gfxScreen_t screenPos);
void drawPixel(int x, int y, char r, char g, char b, u8* screen);
//----- 
void gfxDrawSprite(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y);
void gfxDrawSpriteBlend(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y, int alpha);
};

#endif
