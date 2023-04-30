#include "application.h"
#include "input.h"
#include "player.h"

#define FONT(f) self->fonts[f]
#define SPRITE(s) &self->sprites[s]
#define INPUT_MANAGER (safe_input_manager){.applet=&self->applet}

void _application_update(app* self)
{
    int darumadrop = self->add_font(self, "DarumadropOne-Regular");
    int roboto = self->add_font(self, "Roboto-Light");
    
    int main_menu = self->add_sprite(self, "mainmenu");
    int customer_screen = self->add_sprite(self, "customer-screen");
    int kitchen = self->add_sprite(self, "kitchen");
    
    int screen = 0;
    
    int debug = 0;
    char debug_fonts[64];
    char debug_sprites[64];
    
    safe_input_manager screen_input = INPUT_MANAGER;
    safe_input_manager debug_input = INPUT_MANAGER;
    
    player game_player = create_player(NULL, FONT(darumadrop));
    
    while (keep_applet(self->applet.window_handle))
    {
        // UPDATING //
        switch (screen) 
        {
        case 0:
            if (safe_key_press(&screen_input, KEY_ENTER)) screen = 1;
            break;
            
        case 1:
        default:
            if (safe_key_press(&debug_input, KEY_I)) debug = !debug;
            update_player(&game_player, &self->applet, &screen);
            break;
        }
        
        // DRAWING //
        begin_drawing();
            draw_text_center(FONT(darumadrop), "Hello, World!", self->width / 2, self->height / 2 - 80, 80.0f, BLACK);
            
            switch (screen)
            {
            case 0:
                draw_sprite(SPRITE(main_menu), 0, 0, 1.0f, 0.0f, WHITE);
                break;
                
            case 1:
                draw_sprite(SPRITE(customer_screen), 0, 0, 1.0f, 0.0f, WHITE);
                draw_player(&game_player);
                break;
            
            case 2:
                draw_sprite(SPRITE(kitchen), 0, 0, 1.0f, 0.0f, WHITE);
                draw_player(&game_player);
            default:
                break;
            }

            if (debug)
            {
                sprintf(debug_fonts, "Fonts Loaded: %d", self->fonts_count);
                sprintf(debug_sprites, "Sprites Loaded: %d", self->sprites_count);
                draw_text(FONT(roboto), debug_fonts, get_mouse_x(&self->applet) + 14, get_mouse_y(&self->applet), 28.0f, WHITE);
                draw_text(FONT(roboto), debug_sprites, get_mouse_x(&self->applet) + 14, get_mouse_y(&self->applet) + 28, 28.0f, WHITE);
            }
            
            clear_screen(WHITE);
        end_drawing(&self->applet);
    }
}

void OnAppletUpdate() { /* to prevent linking errors */ }