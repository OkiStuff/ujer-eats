#include "player.h"

player create_player(sprite* player_sprite, font font_used)
{
    return (player)
    {
        .strikes = 0,
        .waiting = 0,
        .annoyed = 0,
        .mad = 0,
        .score = 0,
        .font_used = font_used,
        .inventory = (struct _player_inventory)
        {
            .coffee = 0,
            .pastries = 0,
            .sandwiches = 0
        },
        
        .player_sprite = player_sprite,
        .position = (vec2){585, 450}
    };
}

void draw_player(player* self)
{
    draw_rectangle_vec2(self->position, (vec2){50, 50}, WHITE);
}

void update_player(player* self, Applet* applet, int* screen)
{
    // add delta time
    if (key_down(applet, KEY_W)) self->position.y -= PLAYER_MOVE_SPEED;
    if (key_down(applet, KEY_A)) self->position.x -= PLAYER_MOVE_SPEED;
    if (key_down(applet, KEY_D)) self->position.x += PLAYER_MOVE_SPEED;
    if (key_down(applet, KEY_S)) self->position.y += PLAYER_MOVE_SPEED;
    
    switch (*screen)
    {
    case 1:
        if (self->position.x > 1250)
        {
            *screen = 2;
            self->position.x = 10;
        }
        
        break;

    case 2:
        if (self->position.x < 5)
        {
            *screen = 1;
            self->position.x = 1250;
        }

        break;
    }
    
    if (self->position.x > 1250)
    {
        *screen = 2;
        self->position = (vec2){10, 450};
    }
}