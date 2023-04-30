#ifndef UJER_EATS_PLAYER_H
#define UJER_EATS_PLAYER_H

#define PLAYER_MOVE_SPEED 5

#include <Muzzle.h>
#include <stdint.h>

typedef struct _player
{
    int strikes;
    int waiting;
    int annoyed;
    int mad;
    
    vec2 position;
    sprite* player_sprite;
    font font_used;
    
    struct _player_inventory 
    {
        int coffee;
        int sandwiches;
        int pastries;
    } inventory;
    
    int score;
} player;

player create_player(sprite* player_sprite, font font_used);
void draw_player(player* self);
void update_player(player* self, Applet* applet, int* screen);

#endif //UJER_EATS_PLAYER_H