#include <SDL2/SDL.h>
#include <string>

class LTexture {
    public:
    LTexture();
    ~LTexture();
    bool loadFromFile(std::string path);
    void free();
    void render(int x, int y, SDL_Rect* clip = NULL);
    int getWidth();
    int getHeight();
    void setRenderer(SDL_Renderer* renderer);

    private:
    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;
    int mWidth;
    int mHeight;
};