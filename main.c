#define MUZZLE_DEPS
#define STBTT_RASTERIZER_VERSION 1 // weird fix to allow font to work
#include <Muzzle.h>
#include "include/application.h"

int main()
{
    app game = application("ujer eats", 1280, 720);
    
    game.initialize(&game);
    game.update(&game);
    game.quit(&game);
    
    return 0;
}