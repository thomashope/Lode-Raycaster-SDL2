//
//  SDLsetup.h
//
//  Created by Thomas Joseph Hope on 09/09/2014.
//

#ifndef doomLike_SDLsetup_h
#define doomLike_SDLsetup_h


#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window* win;
SDL_Renderer* ren;


// log an sdl error to the output stream of our choice
void logSDLError(std::ostream &os, const std::string &msg);
// loads a BMP image into a texture on the rendering device
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

// draw and SDL_renderer to and SDL_texture at position x,y
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
// same deal but with specified width and height
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

bool initEverything();
bool initSDL();
bool createWindow();
bool createRenderer();
void setupRenderer();

bool initEverything() {
    
    if ( !initSDL() ) { return false; }
    
    if ( !createWindow() ) { return false; }
    
    if ( !createRenderer() ) { return false; }
    
    setupRenderer();
    
    return true;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(std::cout, "SDL_Init");
        return false;
    }
    return true;
}

bool createWindow() {
    win = SDL_CreateWindow("Doom#Like", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        logSDLError(std::cout, "SDL_CreateWindow");
        SDL_Quit();
        return false;
    }
    return true;
}

bool createRenderer() {
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        logSDLError(std::cout, "SDL_CreateRenderer");
        SDL_Quit();
        return false;
    }
    return true;
}

void setupRenderer() {
    SDL_RenderSetLogicalSize(ren, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}

void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h) {
    //set up the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    renderTexture(tex, ren, x, y, w, h);
}


#endif
