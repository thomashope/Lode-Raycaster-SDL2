/*

InstantCG 20150330

InstantCG is a derivative work of QuickCG by Thomas Hope.
The aim is for InstantCG to be a drop in replacement for QuickCG using SDL2
and to build on QuickCG to include functionality that is only availible in
SDL2.

You can find more about InstantCG https://github.com/Cyphre117/InstantCG

The below legal notice is preserved from the original QuickCG

QuickCG 20071121

Copyright (c) 2004-2007, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef INSTANTCG_H
#define INSTANTCG_H

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

namespace InstantCG
{
    
////////////////////////////////////////////////////////////////////////////////
//COLOR STRUCTS/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct ColorRGB8bit;
//a color with 3 components: r, g and b
struct ColorRGB
{
  int r;
  int g;
  int b;
  
  ColorRGB(Uint8 r, Uint8 g, Uint8 b);
  ColorRGB(const ColorRGB8bit& color);
  ColorRGB();
};
  
ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator*(const ColorRGB& color, int a);
ColorRGB operator*(int a, const ColorRGB& color);
ColorRGB operator/(const ColorRGB& color, int a);
bool operator==(const ColorRGB& color, const ColorRGB& color2);
bool operator!=(const ColorRGB& color, const ColorRGB& color2);

static const ColorRGB RGB_Black    (  0,   0,   0);
static const ColorRGB RGB_Red      (255,   0,   0);
static const ColorRGB RGB_Green    (  0, 255,   0);
static const ColorRGB RGB_Blue     (  0,   0, 255);
static const ColorRGB RGB_Cyan     (  0, 255, 255);
static const ColorRGB RGB_Magenta  (255,   0, 255);
static const ColorRGB RGB_Yellow   (255, 255,   0);
static const ColorRGB RGB_White    (255, 255, 255);
static const ColorRGB RGB_Gray     (128, 128, 128);
static const ColorRGB RGB_Grey     (192, 192, 192);
static const ColorRGB RGB_Maroon   (128,   0,   0);
static const ColorRGB RGB_Darkgreen(  0, 128,   0);
static const ColorRGB RGB_Navy     (  0,   0, 128);
static const ColorRGB RGB_Teal     (  0, 128, 128);
static const ColorRGB RGB_Purple   (128,   0, 128);
static const ColorRGB RGB_Olive    (128, 128,   0);

//a color with 3 components: r, g and b
struct ColorRGB8bit
{
  Uint8 r;
  Uint8 g;
  Uint8 b;
  
  ColorRGB8bit(Uint8 r, Uint8 g, Uint8 b);
  ColorRGB8bit(const ColorRGB& color);
  ColorRGB8bit();
};
  
//a color with 3 components: h, s and l
struct ColorHSL
{
  int h;
  int s;
  int l;

  ColorHSL(Uint8 h, Uint8 s, Uint8 l);
  ColorHSL();
};

//a color with 3 components: h, s and v
struct ColorHSV
{
  int h;
  int s;
  int v;
  
  ColorHSV(Uint8 h, Uint8 s, Uint8 v);
  ColorHSV();
};

////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

extern int w;
extern int h;
extern SDL_Window*   win;
extern SDL_Renderer* ren;

////////////////////////////////////////////////////////////////////////////////
//BASIC SCREEN FUNCTIONS////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void screen(int width = 640, int height = 400, bool fullscreen = false, const std::string& text = " ");
void redraw();
void cls(const ColorRGB& color = RGB_Black);

////////////////////////////////////////////////////////////////////////////////
//NON GRAPHICAL FUNCTIONS///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool done(bool quit_if_esc = true, bool delay = true);
void end();
inline unsigned long getTicks() { return SDL_GetTicks(); } // milliseconds since SDL was initialised
inline double getTime() { return SDL_GetTicks() / 1000.0; } // seconds since SDL was initialised

////////////////////////////////////////////////////////////////////////////////
//2D SHAPES/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void horLine(int y, int x1, int x2, const ColorRGB& color); // draws a horizontal line
void verLine(int x, int y1, int y2, const ColorRGB& color); // draws a verticle line
void drawLine(int x1, int y1, int x2, int y2, const ColorRGB& color); // draws a line
inline void line(int x1, int y1, int x2, int y2, const ColorRGB& color) // shortcut for drawLine()
{ drawLine(x1, y1, x2, y2, color); }

} // end of namespace InstantCG

#endif
