/**
 * 2D drawing library functions.
 */

#include "HRender.h"
#include <3ds.h>
#include <cmath>
#include <string.h>
#include <stdio.h>

Render::Render()
{

}

void Render::screenRender()
{
    gfxFlushBuffers();
	gfxSwapBuffers();
	bottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
	topl = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	topr = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
}

void Render::drawPixel(int x, int y, char r, char g, char b, u8* screen)
{
    if (x >= 400) {
        return; // TODO: Make this check work for lower screen too
    }
	int height=240;
    if (y >= height) {
        return;
    }
	u32 v=(height-1-y+x*height)*3;
    //printf("Blitting: x%d y%d v%lu", x, y, v);
	screen[v]=b;
	screen[v+1]=g;
	screen[v+2]=r;
}

void Render::clearScreen(u8* screen,gfxScreen_t screenPos)
{
	int width;
	int height=240;

	switch(screenPos){
	case GFX_BOTTOM:
		width=320;
		break;
	default:
		width=400;
		break;
	}
	int i, j;
	for(i=1;i<width;i++)
	{
		for(j=1;j<height;j++)
		{
			drawPixel(i,j,0x00,0x00,0x00,screen);
		}
	}
}

void Render::clearTop()
{
    topl = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	topr = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	clearScreen(topl, GFX_TOP);
	clearScreen(topr, GFX_TOP);
}

void Render::clearBottom()
{
  bottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
  clearScreen(bottom, GFX_BOTTOM);
}

void Render::drawLine( int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen)
{
    float xdiff = (x2 - x1);
	float ydiff = (y2 - y1);

	if(xdiff == 0.0f && ydiff == 0.0f) {
		drawPixel(x1, y1,r,g,b,screen);
		return;
	}

	if(fabs(xdiff) > fabs(ydiff)) {
		float xmin, xmax;

		// set xmin to the lower x value given
		// and xmax to the higher value
		if(x1 < x2) {
			xmin = x1;
			xmax = x2;
		} else {
			xmin = x2;
			xmax = x1;
		}

		// draw line in terms of y slope
		float slope = ydiff / xdiff;
		for(float x = xmin; x <= xmax; x += 1.0f) {
			float y = y1 + ((x - x1) * slope);
			drawPixel(x, y,r,g,b,screen);
		}
	} else {
		float ymin, ymax;

		// set ymin to the lower y value given
		// and ymax to the higher value
		if(y1 < y2) {
			ymin = y1;
			ymax = y2;
		} else {
			ymin = y2;
			ymax = y1;
		}

		// draw line in terms of x slope
		float slope = xdiff / ydiff;
		for(float y = ymin; y <= ymax; y += 1.0f) {
			float x = x1 + ((y - y1) * slope);
			
			drawPixel(x, y ,r,g,b,screen);
		}
	}
}
void Render::drawRect( int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen)
{
	drawLine( x1, y1, x2, y1, r, g, b, screen);
	drawLine( x2, y1, x2, y2, r, g, b, screen);
	drawLine( x1, y2, x2, y2, r, g, b, screen);
	drawLine( x1, y1, x1, y2, r, g, b, screen);
}

void Render::drawFillRect(int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen, bool v)
{
	int X1,X2,Y1,Y2,i,j;

	if (x1<x2){ 
		X1=x1;
		X2=x2;
	} else { 
		X1=x2;
		X2=x1;
	} 

	if (y1<y2){ 
		Y1=y1;
		Y2=y2;
	} else { 
		Y1=y2;
		Y2=y1;
	} 
	for(i=X1;i<=X2;i++){
		for(j=Y1;j<=Y2;j++){
            // Try to avoid OOB blitting
            if (!(i < 0 || i >= 400 || j < 0 || j >= 240))
                drawPixel(i,j, r, g, b, screen);
		}
	}
}

void Render::drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3,char r,char g, char b,u8 *screen)
{
  drawLine(x1,y1,x2,y2,r,g,b,screen);
  drawLine(x2,y2,x3,y3,r,g,b,screen);
  drawLine(x3,y3,x1,y1,r,g,b,screen);
}

void Render::drawCircle(int xCen, int yCen, int radius, char r, char g, char b, u8* screen)
{
	int x = 0;
	int y = radius;
	int p = (5 - radius*4)/4;
	drawCircleCircum(xCen, yCen, x, y, r, g, b, screen);
	while(x < y){
		x++;
		if(p < 0){
			p += 2*x+1;
		}
		else{
			y--;
			p += 2*(x-y)+1;
		}
		drawCircleCircum(xCen, yCen, x, y, r, g, b, screen);
	}
}

void Render::drawFillCircle(int xCen, int yCen, int radius, char r, char g, char b, u8* screen)
{
	drawCircle(xCen, yCen, radius, r, g, b, screen);
	int x,y;
	for(y = -radius;y <= radius;y++){
		for(x = -radius;x <= radius;x++)
			if(x*x + y*y <= radius*radius + radius * .8f)
				drawPixel(xCen + x, yCen + y, r, g, b, screen);
	}
}

void Render::drawCircleCircum(int cx, int cy, int x, int y, char r, char g, char b, u8* screen)
{
	//int tx, ty;

	if(x == 0){
		drawPixel(cx, cy + y, r, g, b, screen);
		drawPixel(cx, cy - y, r, g, b, screen);
		drawPixel(cx + y, cy, r, g, b, screen);
		drawPixel(cx - y, cy, r, g, b, screen);
	}
	if(x == y){
		drawPixel(cx + x, cy + y, r, g, b, screen);
		drawPixel(cx - x, cy + y, r, g, b, screen);
		drawPixel(cx + x, cy - y, r, g, b, screen);
		drawPixel(cx - x, cy - y, r, g, b, screen);
	}
	if(x < y){
		drawPixel(cx + x, cy + y, r, g, b, screen);
		drawPixel(cx - x, cy + y, r, g, b, screen);
		drawPixel(cx + x, cy - y, r, g, b, screen);
		drawPixel(cx - x, cy - y, r, g, b, screen);
		drawPixel(cx + y, cy + x, r, g, b, screen);
		drawPixel(cx - y, cy + x, r, g, b, screen);
		drawPixel(cx + y, cy - x, r, g, b, screen);
		drawPixel(cx - y, cy - x, r, g, b, screen);
	}
}

//-----------sprite/.bin drawing stolen from someone else LOL!-------------

void Render::gfxDrawSprite(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y)
{
	if(!spriteData)return;

	u16 fbWidth, fbHeight;
	u8* fbAdr=gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

	if(x+width<0 || x>=fbWidth)return;
	if(y+height<0 || y>=fbHeight)return;

	u16 xOffset=0, yOffset=0;
	u16 widthDrawn=width, heightDrawn=height;

	if(x<0)xOffset=-x;
	if(y<0)yOffset=-y;
	if(x+width>=fbWidth)widthDrawn=fbWidth-x;
	if(y+height>=fbHeight)heightDrawn=fbHeight-y;
	widthDrawn-=xOffset;
	heightDrawn-=yOffset;

	int j;
	for(j=yOffset; j<yOffset+heightDrawn; j++)
	{
		memcpy(&fbAdr[((x+xOffset)+(y+j)*fbWidth)*3], &spriteData[((xOffset)+(j)*width)*3], widthDrawn*3);
	}
}
void Render::gfxDrawSpriteBlend(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y, int alpha)
{
	if(!spriteData)return;

	u16 fbWidth, fbHeight;
	u8* fbAdr=gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

	if(x+width<0 || x>=fbWidth)return;
	if(y+height<0 || y>=fbHeight)return;

	u16 xOffset=0, yOffset=0;
	u16 widthDrawn=width, heightDrawn=height;

	if(x<0)xOffset=-x;
	if(y<0)yOffset=-y;
	if(x+width>=fbWidth)widthDrawn=fbWidth-x;
	if(y+height>=fbHeight)heightDrawn=fbHeight-y;
	widthDrawn-=xOffset;
	heightDrawn-=yOffset;

	//TODO : optimize
	fbAdr+=(y+yOffset)*fbWidth*3;
	spriteData+=yOffset*width*3;
	int j, i;
	for(j=yOffset; j<yOffset+heightDrawn; j++)
	{
		u8* fbd=&fbAdr[(x+xOffset)*3];
		u8* data=&spriteData[(xOffset)*3];
		for(i=xOffset; i<xOffset+widthDrawn; i++)
		{
			if ((data[0]+data[1]+data[2])!=255*3)
			{
			fbd[0] = ((data[0] * alpha)+(fbd[0] * (255 - alpha))) / 256;
			fbd[1] = ((data[1] * alpha)+(fbd[1] * (255 - alpha))) / 256;
			fbd[2] = ((data[2] * alpha)+(fbd[2] * (255 - alpha))) / 256;
			}
			fbd+=3;
			data+=3;
		}
		fbAdr+=fbWidth*3;
		spriteData+=width*3;
	}
}
