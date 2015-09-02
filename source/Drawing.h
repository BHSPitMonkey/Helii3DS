/* 
 * File:   Drawing.h
 * Author: stephen
 *
 * Created on August 7, 2015, 2:23 AM
 */

#ifndef DRAWING_H
#define	DRAWING_H

// Pure geometry data
class Rectangle {
public:
    int x;
    int y;
    int width;
    int height;
    Rectangle();
private:

};

// Drawable quadrilateral
class Quad {
public:
    Quad();
    void SetRectangle(Rectangle r);
    void SetFillColor(char r, char g, char b);
    void Draw(bool v=0);
private:
    Rectangle _rect;
    char _r;
    char _g;
    char _b;
};

class Sprite {
public:
    Sprite();
    int GetX();
    int GetY();
    void SetX(int x);
    void SetY(int y);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetPosition(int x, int y);
    void SetVisible(bool visible);
    bool CollidesWith(Rectangle rect, float x, float y);
    void SetPlaceholderColor(int r, int g, int b);
    void Move(int dx, int dy);
    void Draw();
private:
    int _x;
    int _y;
    int _width;
    int _height;
    int _visible;
    int _r;
    int _g;
    int _b;
};

#endif	/* DRAWING_H */

