#ifndef UJER_EATS_GAME_STATE_H
#define UJER_EATS_GAME_STATE_H

#define PLAYER_MOVE_SPEED 5
#define GAME_CUSTOMERS_AMOUNT 5

#include <Muzzle.h>
#include <stdint.h>
#include "collision.h"
#define GET_RANDOM_NUMBER(max) (rand() % (max + 1))

enum _CUSTOMERS_EMOTIONS
{
    CUSTOMER_EMOTION_WAITING = 0,
    CUSTOMER_EMOTION_ANNOYED = 1,
    CUSTOMER_EMOTION_MAD = 2
};

typedef struct _customer
{
    int emotion;
    int pos_in_line;
    float timer;

    struct _customer_order
    {
        int coffee;
        int pastries;
        int sandwiches;
    } order;
} customer;

typedef struct _game_state
{
    int strikes;
    int waiting;
    int annoyed;
    int mad;
    
    int money;
    
    int total_in_line;
    customer* customers;
    
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
} game_state;

customer create_customer(int pos_in_line);
void update_customers(customer* self, game_state* game);
void draw_customers(customer* self, game_state* game);

game_state create_game_state(sprite* player_sprite, font font_used);
void draw_game_state(game_state* self, int screen);
void update_game_state(game_state* self, Applet* applet, int* screen);

void unload_game_state(game_state* self);

#endif //UJER_EATS_GAME_STATE_H