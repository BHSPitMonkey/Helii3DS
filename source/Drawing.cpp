/* 
 * File:   Drawing.cpp
 * Author: stephen
 * 
 * Created on August 7, 2015, 2:23 AM
 */

#include <stdio.h>
#include <sfil.h>
#include <math.h>
#include "globals.h"
#include "Drawing.h"
#include "CaveManager.h"

void Drawing::Init()
{
    sf2d_init();
}

void Drawing::Finish()
{
    sf2d_fini();
}

void Drawing::SetClearColor(char r, char g, char b, char a)
{
    sf2d_set_clear_color(RGBA8(r, g, b, a));
}

void Drawing::StartTopLeftFrame()
{
    sf2d_start_frame(GFX_TOP, GFX_LEFT);
}

void Drawing::StartBottomFrame()
{
    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
}

void Drawing::EndFrame()
{
    sf2d_end_frame();
}

void Drawing::SwapBuffers()
{
    sf2d_swapbuffers();
}

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
    sf2d_draw_rectangle_rotate(
        _rect.x,
        _rect.y,
        _rect.width,
        _rect.height,
        RGBA8(_r, _g, _b, 0xFF),
        0.0 // radians
    );
}

Image::Image()
{
    _tex = 0;
}

Image::~Image()
{
    if (_tex) {
        sf2d_free_texture(_tex);
    }
}

void Image::LoadImage(const char * filename)
{
    _tex = sfil_load_PNG_file(filename, SF2D_PLACE_RAM); // TODO: Different place?
}

sf2d_texture * Image::GetTexture()
{
    return _tex;
}

Sprite::Sprite()
{
    _x = _y = _width = _height = 0;
    _r = 255;
    _g = 255;
    _b = 0;
    _alpha = 0xFF;
    _visible = true;
    _image = 0;
}

int Sprite::GetX()
{
    return _x;
}

int Sprite::GetY()
{
    return _y;
}

unsigned char Sprite::GetOpacity()
{
    return _alpha;
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

void Sprite::SetRotation(float degrees)
{
    _rot = degrees * (M_PI / 180);
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

void Sprite::SetImage(Image * image, int _tile_w, int _tile_h)
{
    _image = image;
    sf2d_texture * tex = 0;
    if ((_image) && (tex = _image->GetTexture())) {
        _width = tex->width;
        _height = tex->height;
    }
}

void Sprite::Move(int dx, int dy)
{
    _x += dx;
    _y += dy;
}

void Sprite::Draw()
{
    if (_visible && _width && _height) {
        // Try to draw image if possible
        sf2d_texture * tex = 0;
        if ((_image) && (tex = _image->GetTexture())) {
            sf2d_draw_texture_part_rotate_scale_blend(
                tex,
                _x,
                _y,
                _rot,
                0,
                0,
                tex->width,
                tex->height,
                _width / tex->width,
                _height / tex->height,
                RGBA8(0xFF, 0xFF, 0xFF, _alpha)
            );
        }
        // Fall back to colored rectangle if no texture present
        else {
            sf2d_draw_rectangle_rotate(
                _x,
                _y,
                _width,
                _height,
                RGBA8(_r, _g, _b, _alpha),
                _rot
            );
        }
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
            "Coll: %d %d %d %d, %d %d %d %d\n",
            rect.x,
            rect.y,
            rect.width,
            rect.height,
            _x,
            _y,
            (int) _width,
            (int) _height
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

void Sprite::SetOpacity(u8 alpha)
{
    _alpha = alpha;
}