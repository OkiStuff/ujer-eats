#include "game_state.h"

game_state create_game_state(sprite* player_sprite, font font_used)
{
    customer* temp = MZ_CALLOC(GAME_CUSTOMERS_AMOUNT, sizeof(customer));
    if (temp == NULL) log_status(STATUS_FATAL_ERROR, "Customers could not allocate memory");

    for (int i = 0; i < GAME_CUSTOMERS_AMOUNT; i++)
    {
        temp[i] = create_customer(i);
    }
    
    return (game_state)
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
        .total_in_line = GAME_CUSTOMERS_AMOUNT,
        .money = 0,
        .customers = temp,
        .player_sprite = player_sprite,
        .position = (vec2){585, 450}
    };
}

void draw_game_state(game_state* self, int screen)
{
    draw_sprite_vec2(self->player_sprite, self->position, 1.0f, 0.0f, WHITE);

    static char waiting[128];
    static char annoyed[128];
    static char mad[128];
    static char strikes[128];
    static char money[128];
    
    static char coffee[128];
    static char pastires[128];
    static char sandwiches[128];

    sprintf_s(waiting, 128, "waiting: %d", self->waiting);
    sprintf_s(annoyed, 128, "annoyed: %d", self->annoyed);
    sprintf_s(mad, 128, "mad: %d", self->mad);
    sprintf_s(strikes, 128, "strikes: %d", self->strikes);
    sprintf_s(money, 128, "money: $%d", self->money);
    
    sprintf_s(coffee, 128, "coffee: %d/%d", self->inventory.coffee, self->customers[0].order.coffee);
    sprintf_s(pastires, 128, "pastries: %d/%d", self->inventory.pastries, self->customers[0].order.pastries);
    sprintf_s(sandwiches, 128, "sandwiches: %d/%d", self->inventory.sandwiches, self->customers[0].order.sandwiches);
    
    draw_text(self->font_used, waiting, 0, 0, 40.f, WHITE);
    draw_text(self->font_used, annoyed, 0, 40, 40.f, ORANGE);
    draw_text(self->font_used, mad, 0, 80, 40.f, RED);
    draw_text(self->font_used, strikes, 0, 120, 40.f, BLACK);

    draw_text(self->font_used, pastires, 0, 560, 40.f, WHITE);
    draw_text(self->font_used, sandwiches, 0, 600, 40.f, WHITE);
    draw_text(self->font_used, coffee, 0, 640, 40.f, WHITE);
    draw_text(self->font_used, money, 0, 680, 40.f, GREEN);
    
    if (screen == 1) draw_customers(self->customers, self);
}

void update_game_state(game_state* self, Applet* applet, int* screen)
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
        
        // Player Bounds
        if (self->position.x < 80) self->position.x += PLAYER_MOVE_SPEED;
        if (self->position.y < 410) self->position.y += PLAYER_MOVE_SPEED;
        if (self->position.y > 600) self->position.y -= PLAYER_MOVE_SPEED;
        
        break;

    case 2:
        if (self->position.x < 5)
        {
            *screen = 1;
            self->position.x = 1250;
        }
        
        // Player Bounds
        if (self->position.y > 580) self->position.y -= PLAYER_MOVE_SPEED;
        if (self->position.x > 1140) self->position.x -= PLAYER_MOVE_SPEED;
        if (self->position.y < 90) self->position.y += PLAYER_MOVE_SPEED;
        if (self->position.x < 330 && self->position.y < 410) self->position.y += PLAYER_MOVE_SPEED;
        if (self->position.y <= 350 && self->position.x < 340) self->position.x += PLAYER_MOVE_SPEED;
        
        break;
    }
}

void unload_game_state(game_state* self)
{
    MZ_FREE(self->customers);
}