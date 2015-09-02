/* 
 * File:   Drawing.cpp
 * Author: stephen
 * 
 * Created on August 7, 2015, 2:23 AM
 */

#include <stdio.h>
#include "globals.h"
#include "Drawing.h"
#include "CaveManager.h"

Rectangle::Rectangle()
{
}

Quad::Quad()
{
    _r = _g = _b = 255;
}

void Quad::SetRectangle(Rectangle r)
{
    _rect = r;
}

void Quad::SetFillColor(char r, char g, char b)
{
    _r = r;
    _g = g;
    _b = b;
}

void Quad::Draw(bool v)
{
    rend.drawFillRect(
        _rect.x,
        _rect.y,
        _rect.x + _rect.width - 1,
        _rect.y + _rect.height - 1,
        _r,
        _g,
        _b,
        rend.topl,
        v
    );
}

Sprite::Sprite()
{
    _x = _y = _width = _height = 0;
    _r = 255;
    _g = 255;
    _b = 0;
    _visible = true;
}

int Sprite::GetX()
{
    return _x;
}

int Sprite::GetY()
{
    return _y;
}

void Sprite::SetX(int x)
{
    _x = x;
}

void Sprite::SetY(int y)
{
    _y = y;
}

void Sprite::SetWidth(int width)
{
    _width = width;
}

void Sprite::SetHeight(int height)
{
    _height = height;
}
    
void Sprite::SetPosition(int x, int y)
{
    _x = x;
    _y = y;
}

void Sprite::SetVisible(bool visible)
{
    _visible = visible;
}

void Sprite::Move(int dx, int dy)
{
    _x += dx;
    _y += dy;
}

void Sprite::Draw()
{
    if (_visible && _width && _height) {
        // TODO: Replace with image
        rend.drawFillRect(
            _x,
            _y,
            _x + _width,
            _y + _height,
            _r,
            _g,
            _b,
            rend.topl
        );
    }
}

// TODO: What were x and y again?
bool Sprite::CollidesWith(Rectangle rect, float x, float y)
{
    bool collided = (rect.x < _x + _width &&
       rect.x + rect.width > _x &&
       rect.y < _y + _height &&
       rect.height + rect.y > _y);
    
    if (collided) {
        printf(
            "Collision: %d %d %d %d, %d %d %d %d",
            rect.x,
            rect.y,
            rect.width,
            rect.height,
            _x,
            _y,
            _width,
            _height
        );
    }
    
    return collided;
}

void Sprite::SetPlaceholderColor(int r, int g, int b)
{
    _r = r;
    _g = g;
    _b = b;
}