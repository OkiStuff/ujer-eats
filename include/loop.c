#include "application.h"
#include "input.h"
#include "game_state.h"
#include <stdlib.h>
#include <time.h>

#include "external/raudio/src/raudio.h"

#define FONT(f) self->fonts[f]
#define SPRITE(s) &self->sprites[s]
#define INPUT_MANAGER (safe_input_manager){.applet=&self->applet}

void _application_update(app* self)
{
    srand(time(NULL));
    InitAudioDevice();
    
    int darumadrop = self->add_font(self, "DarumadropOne-Regular");
    int roboto = self->add_font(self, "Roboto-Light");
    
    int main_menu = self->add_sprite(self, "mainmenu");
    int customer_screen = self->add_sprite(self, "customer-screen");
    int kitchen = self->add_sprite(self, "kitchen");
    int character = self->add_sprite(self, "character");
    
    int screen = 0;
    
    int debug = 0;
    char debug_fonts[64];
    char debug_sprites[64];
    
    Music background_music = LoadMusicStream("../assets/music/Bossa-Antigua.mp3");
    PlayMusicStream(background_music);
    
    safe_input_manager screen_input = INPUT_MANAGER;
    safe_input_manager debug_input = INPUT_MANAGER;
    
    game_state game = create_game_state(SPRITE(character), FONT(darumadrop));

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
            update_game_state(&game, &self->applet, &screen);
            break;
        }
        
        // DRAWING //
        begin_drawing();
            //draw_text_center(FONT(darumadrop), "Hello, World!", self->width / 2, self->height / 2 - 80, 80.0f, BLACK);
            
            switch (screen)
            {
            case 0:
                // Main Menu
                draw_sprite(SPRITE(main_menu), 0, 0, 1.0f, 0.0f, WHITE);
                break;
                
            case 1:
                // Cashier Screen
                draw_sprite(SPRITE(customer_screen), 0, 0, 1.0f, 0.0f, WHITE);
                draw_game_state(&game, screen);
                break;
            
            case 2:
                // Kitchen
                draw_sprite(SPRITE(kitchen), 0, 0, 1.0f, 0.0f, WHITE);
                draw_game_state(&game, screen);
            default:
                break;
            }

            //if (debug)
            //{
            //    sprintf(debug_fonts, "Fonts Loaded: %d", self->fonts_count);
            //    sprintf(debug_sprites, "Sprites Loaded: %d", self->sprites_count);
            //    draw_text(FONT(roboto), debug_fonts, get_mouse_x(&self->applet) + 14, get_mouse_y(&self->applet), 28.0f, WHITE);
            //    draw_text(FONT(roboto), debug_sprites, get_mouse_x(&self->applet) + 14, get_mouse_y(&self->applet) + 28, 28.0f, WHITE);
            //}
            
            clear_screen(WHITE);
        end_drawing(&self->applet);
        UpdateMusicStream(background_music);
    }

    UnloadMusicStream(background_music);
    CloseAudioDevice();
    unload_game_state(&game);
}

void OnAppletUpdate() { /* to prevent linking errors */ }