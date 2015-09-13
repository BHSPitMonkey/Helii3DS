/* 
 * File:   Drawing.h
 * Author: stephen
 *
 * Created on August 7, 2015, 2:23 AM
 */

#ifndef DRAWING_H
#define	DRAWING_H

#include <sf2d.h>

class Drawing {
public:
    static void Init();
    static void Finish();
    static void SetClearColor(char r, char g, char b, char a = 0xFF);
    static void StartTopLeftFrame();
    static void StartBottomFrame();
    static void EndFrame();
    static void SwapBuffers();
};

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

class Image {
public:
    Image();
    ~Image();
    void LoadImage(const char * filename);
    sf2d_texture * GetTexture();
private:
    sf2d_texture * _tex;
};

class Sprite {
public:
    Sprite();
    int GetX();
    int GetY();
    u8 GetOpacity();
    void SetX(int x);
    void SetY(int y);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetRotation(float degrees);
    void SetPosition(int x, int y);
    void SetVisible(bool visible);
    void SetImage(Image * image, int _tile_w = 0, int _tile_h = 0);
    void DefineCollisionRectangle(int x, int y, int w, int h);
    bool CollidesWith(Rectangle rect, float x, float y);
    void SetPlaceholderColor(int r, int g, int b);
    void SetTint(u8 r, u8 g, u8 b);
    void SetOpacity(u8 alpha);
    void Move(int dx, int dy);
    void Draw();
private:
    int _x;
    int _y;
    float _width;
    float _height;
    float _rot;
    int _visible;
    Image * _image;
    int _r;
    int _g;
    int _b;
    u8 _alpha;
    Rectangle _collRect;
    u8 _tintR;
    u8 _tintG;
    u8 _tintB;
};

#endif	/* DRAWING_H */

