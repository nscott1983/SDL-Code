#include "LButton.h"

LButton::LButton() {
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;
        if (x < mPosition.x) {
            
        }
    }
}