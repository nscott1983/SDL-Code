#pragma once
#include <SDL2/SDL.h>


enum LButtonSprite {
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_MOUSE_TOTAL = 4
};

class LButton {
    public:
    LButton();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    void render();
    
    private:
    SDL_Point mPosition;
    LButtonSprite mCurrentSprite;
};