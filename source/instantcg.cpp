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

#include "instantcg.h"

namespace InstantCG
{

////////////////////////////////////////////////////////////////////////////////
//VARIABLES/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int w; //width of the screen
int h; //height of the screen
SDL_Window*   win; //The window
SDL_Renderer* ren; //The renderer

SDL_Event event = {0};

////////////////////////////////////////////////////////////////////////////////
//BASIC SCREEN FUNCTIONS////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//The screen function: sets up the window for 32-bit color graphics.
//Creates a graphical screen of width*height pixels in 32-bit color.
//Set fullscreen to 0 for a window, or to 1 for fullscreen output
//text is the caption or title of the window
//also inits SDL
void screen(int width, int height, bool fullscreen, const std::string& text)
{
	w = width;
	h = height;


	// TODO: add fullscreen option
	// TODO: add error handeling
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow(text.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
void redraw()
{
    SDL_RenderPresent(ren);
}
void cls(const ColorRGB& color)
{
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
    SDL_RenderClear(ren);
}

////////////////////////////////////////////////////////////////////////////////
//NON GRAPHICAL FUNCTIONS///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//Returns 1 if you close the window or press the escape key. Also handles everything thats needed per frame.
bool done(bool quit_if_esc, bool delay)
{
	if (delay) SDL_Delay(5); //So it consumes less processing power
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) return true;
		if (quit_if_esc &&
			event.type == SDL_KEYDOWN &&
			event.key.keysym.sym == SDLK_ESCAPE) return true;
	}
	return false;
}

//Ends the program
void end()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	std::exit(1);
}

////////////////////////////////////////////////////////////////////////////////
//2D SHAPES/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void horLine(int y, int x1, int x2, const ColorRGB& color)
{  
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
	SDL_RenderDrawLine(ren, x1, y, x2, y); 
}
    
void verLine(int x, int y1, int y2, const ColorRGB& color)
{
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
	SDL_RenderDrawLine(ren, x, y1, x, y2); 
}

void drawLine(int x1, int y1, int x2, int y2, const ColorRGB& color)
{
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
	SDL_RenderDrawLine(ren, x1, y1, x2, y2); 
}

////////////////////////////////////////////////////////////////////////////////
//COLOR STRUCTS/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}
ColorRGB::ColorRGB(const ColorRGB8bit& color)
{
  this->r = color.r;
  this->g = color.g;
  this->b = color.b;
}
ColorRGB::ColorRGB()
{
  this->r = 0;
  this->g = 0;
  this->b = 0;
}
ColorRGB8bit::ColorRGB8bit(Uint8 r, Uint8 g, Uint8 b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}
ColorRGB8bit::ColorRGB8bit(const ColorRGB& color)
{
  this->r = color.r;
  this->g = color.g;
  this->b = color.b;
}
ColorRGB8bit::ColorRGB8bit()
{
  this->r = 0;
  this->g = 0;
  this->b = 0;
}

//Add two colors
ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2)
{
  ColorRGB c;
  c.r = color.r + color2.r;
  c.g = color.g + color2.g;
  c.b = color.b + color2.b;
  return c;
}

//Subtract two colors
ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2)
{
  ColorRGB c;
  c.r = color.r - color2.r;
  c.g = color.g - color2.g;
  c.b = color.b - color2.b;
  return c;
}

//Multiplies a color with an integer
ColorRGB operator*(const ColorRGB& color, int a)
{
  ColorRGB c;
  c.r = color.r * a;
  c.g = color.g * a;
  c.b = color.b * a;
  return c;
}

//Multiplies a color with an integer
ColorRGB operator*(int a, const ColorRGB& color)
{
  ColorRGB c;
  c.r = color.r * a;
  c.g = color.g * a;
  c.b = color.b * a;
  return c;
}

//Divides a color through an integer
ColorRGB operator/(const ColorRGB& color, int a)
{
  if(a == 0) return color;
  ColorRGB c;
  c.r = color.r / a;
  c.g = color.g / a;
  c.b = color.b / a;
  return c;
}

//Are both colors equal?
bool operator==(const ColorRGB& color, const ColorRGB& color2)
{
  return(color.r == color2.r && color.g == color2.g && color.b == color2.b);
}

//Are both colors not equal?
bool operator!=(const ColorRGB& color, const ColorRGB& color2)
{
  return(!(color.r == color2.r && color.g == color2.g && color.b == color2.b));
}

ColorHSL::ColorHSL(Uint8 h, Uint8 s, Uint8 l)
{
  this->h = h;
  this->s = s;
  this->l = l;
}
ColorHSL::ColorHSL()
{
  this->h = 0;
  this->s = 0;
  this->l = 0;
}
ColorHSV::ColorHSV(Uint8 h, Uint8 s, Uint8 v)
{
  this->h = h;
  this->s = s;
  this->v = v;
}
ColorHSV::ColorHSV()
{
  this->h = 0;
  this->s = 0;
  this->v = 0;
}

////////////////////////////////////////////////////////////////////////////////
//COLOR CONVERSIONS/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
Convert colors from one type to another
r=red  g=green  b=blue  h=hue  s=saturation  l=lightness  v=value
Color components from the color structs are Uint8's between 0 and 255
color components used in the calculations are normalized between 0.0-1.0
*/

//Converts an RGB color to HSL color
ColorHSL RGBtoHSL(const ColorRGB& colorRGB)
{
  float r, g, b, h = 0, s = 0, l; //this function works with floats between 0 and 1
  r = colorRGB.r / 256.0;
  g = colorRGB.g / 256.0;
  b = colorRGB.b / 256.0;

  float maxColor = std::max(r, std::max(g, b));
  float minColor = std::min(r, std::min(g, b));

  if(minColor == maxColor) //R = G = B, so it's a shade of grey
  {
    h = 0; //it doesn't matter what value it has
    s = 0;
    l = r; //doesn't matter if you pick r, g, or b
  }
  else
  {
    l = (minColor + maxColor) / 2;

    if(l < 0.5) s = (maxColor - minColor) / (maxColor + minColor);
    if(l >= 0.5) s = (maxColor - minColor) / (2.0 - maxColor - minColor);

    if(r == maxColor) h = (g - b) / (maxColor - minColor);
    if(g == maxColor) h = 2.0 + (b - r) / (maxColor - minColor);
    if(b == maxColor) h = 4.0 + (r - g) / (maxColor - minColor);

    h /= 6; //to bring it to a number between 0 and 1
    if(h < 0) h += 1;
  }
  
  ColorHSL colorHSL;
  colorHSL.h = int(h * 255.0);
  colorHSL.s = int(s * 255.0);
  colorHSL.l = int(l * 255.0);
  return colorHSL;
}

//Converts an HSL color to RGB color
ColorRGB HSLtoRGB(const ColorHSL& colorHSL)
{
  float r, g, b, h, s, l; //this function works with floats between 0 and 1
  float temp1, temp2, tempr, tempg, tempb;
  h = colorHSL.h / 256.0;
  s = colorHSL.s / 256.0;
  l = colorHSL.l / 256.0;

  //If saturation is 0, the color is a shade of grey
  if(s == 0) r = g = b = l;
  //If saturation > 0, more complex calculations are needed
  else
  {
    //set the temporary values
    if(l < 0.5) temp2 = l * (1 + s);
    else temp2 = (l + s) - (l * s);
    temp1 = 2 * l - temp2;
    tempr=h + 1.0 / 3.0;
    if(tempr > 1.0) tempr--;
    tempg=h;
    tempb=h-1.0 / 3.0;
    if(tempb < 0.0) tempb++;

    //red
    if(tempr < 1.0 / 6.0) r = temp1 + (temp2 - temp1) * 6.0 * tempr;
    else if(tempr < 0.5) r = temp2;
    else if(tempr < 2.0 / 3.0) r = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
    else r = temp1;
    
     //green
    if(tempg < 1.0 / 6.0) g = temp1 + (temp2 - temp1) * 6.0 * tempg;
    else if(tempg < 0.5) g=temp2;
    else if(tempg < 2.0 / 3.0) g = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
    else g = temp1;

    //blue
    if(tempb < 1.0 / 6.0) b = temp1 + (temp2 - temp1) * 6.0 * tempb;
    else if(tempb < 0.5) b = temp2;
    else if(tempb < 2.0 / 3.0) b = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempb) * 6.0;
    else b = temp1;
  }

  ColorRGB colorRGB;
  colorRGB.r = int(r * 255.0);
  colorRGB.g = int(g * 255.0);
  colorRGB.b = int(b * 255.0);
  return colorRGB;
}

//Converts an RGB color to HSV color
ColorHSV RGBtoHSV(const ColorRGB& colorRGB)
{
  float r, g, b, h = 0.0, s = 0.0, v; //this function works with floats between 0 and 1
  r = colorRGB.r / 256.0;
  g = colorRGB.g / 256.0;
  b = colorRGB.b / 256.0;

  float maxColor = std::max(r, std::max(g, b));
  float minColor = std::min(r, std::min(g, b));

  v = maxColor;

  if(maxColor != 0.0) //avoid division by zero when the color is black
  {
    s = (maxColor - minColor) / maxColor;
  }
  
  if(s == 0.0)
  {
    h = 0.0; //it doesn't matter what value it has
  }
  else
  {
    if(r == maxColor) h = (g - b) / (maxColor - minColor);
    if(g == maxColor) h = 2.0 + (b - r) / (maxColor - minColor);
    if(b == maxColor) h = 4.0 + (r - g) / (maxColor - minColor);

    h /= 6.0; //to bring it to a number between 0 and 1
    if(h < 0.0) h++;
  }

  ColorHSV colorHSV;
  colorHSV.h = int(h * 255.0);
  colorHSV.s = int(s * 255.0);
  colorHSV.v = int(v * 255.0);
  return colorHSV;
}

//Converts an HSV color to RGB color
ColorRGB HSVtoRGB(const ColorHSV& colorHSV)
{
  float r, g, b, h, s, v; //this function works with floats between 0 and 1
  h = colorHSV.h / 256.0;
  s = colorHSV.s / 256.0;
  v = colorHSV.v / 256.0;

  //if saturation is 0, the color is a shade of grey
  if(s == 0.0) r = g = b = v;
  //if saturation > 0, more complex calculations are needed
  else
  {
    float f, p, q, t;
    int i;
    h *= 6.0; //to bring hue to a number between 0 and 6, better for the calculations
    i = int(floor(h)); //e.g. 2.7 becomes 2 and 3.01 becomes 3 or 4.9999 becomes 4
    f = h - i;//the fractional part of h

    p = v * (1.0 - s);
    q = v * (1.0 - (s * f));
    t = v * (1.0 - (s * (1.0 - f)));

    switch(i)
    {
      case 0: r=v; g=t; b=p; break;
      case 1: r=q; g=v; b=p; break;
      case 2: r=p; g=v; b=t; break;
      case 3: r=p; g=q; b=v; break;
      case 4: r=t; g=p; b=v; break;
      case 5: r=v; g=p; b=q; break;
      default: r = g = b = 0; break;
    }
  }
  ColorRGB colorRGB;
  colorRGB.r = int(r * 255.0);
  colorRGB.g = int(g * 255.0);
  colorRGB.b = int(b * 255.0);
  return colorRGB;
}

Uint32 RGBtoINT(const ColorRGB& colorRGB)
{
  return 65536 * colorRGB.r + 256 * colorRGB.g + colorRGB.b;
}

ColorRGB INTtoRGB(Uint32 colorINT)
{
  ColorRGB colorRGB;
  colorRGB.r = (colorINT / 65536) % 256;
  colorRGB.g = (colorINT / 256) % 256;
  colorRGB.b = colorINT % 256;
  return colorRGB;
}  


} // end of namespace InstantCG



