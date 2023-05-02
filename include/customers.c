#include "game_state.h"

customer create_customer(int pos_in_line)
{
    customer temp;
    
    temp.pos_in_line = pos_in_line;
    temp.emotion = CUSTOMER_EMOTION_WAITING;
    temp.order.sandwiches = GET_RANDOM_NUMBER(4) + 1;
    temp.order.coffee = GET_RANDOM_NUMBER(1) ? 1 : 0;
    temp.order.pastries = GET_RANDOM_NUMBER(4) + 1;
    temp.timer = 0.0f;
    
    return temp;
}

void update_customers(customer* self, game_state* game)
{
    for (int i = 0; i < GAME_CUSTOMERS_AMOUNT; i++)
    {
        self[i].timer += get_delta_time();
        
        if (self[i].timer > 120.f)
        {
            if (self[i].emotion == CUSTOMER_EMOTION_MAD)
            {
                //player_self->total_in_line -= 1;
                game->strikes += 1;
                game->score -= 10;
                
                // Reset Customer
                self[i] = create_customer(game->total_in_line); // Change this
                continue;
            }
            
            switch(++self[i].emotion)
            {
            case CUSTOMER_EMOTION_ANNOYED:
                game->annoyed++;
                game->waiting--;
                break;
                
            case CUSTOMER_EMOTION_MAD:
                game->mad++;
                game->annoyed--;
            default:
                break;
            }
            
            self[i].timer = 0.0f;
        }
    }
}

void draw_customers(customer* self, game_state* game)
{
    for (int i = 0; i < GAME_CUSTOMERS_AMOUNT; i++) 
    {
        draw_sprite(game->player_sprite, 524, 180 - (i * 150), 1.0f, 0.0f, WHITE);
    }    
}