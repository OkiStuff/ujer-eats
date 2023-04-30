#include "application.h"

void _application_initialize(app* self)
{
    self->applet = InitializeApplet(self->width, self->height, self->title, MUZZLE_FALSE, MUZZLE_TRUE);
    
    self->fonts_count = 0;
    self->fonts_max = APPLICATION_FONT_SPRITE_SIZE;
    self->fonts = MZ_CALLOC(self->fonts_max, sizeof(font));
    
    self->sprites_count = 0;
    self->sprites_max = APPLICATION_FONT_SPRITE_SIZE;
    self->sprites = MZ_CALLOC(self->sprites_max, sizeof(sprite));
    
    if (self->fonts == NULL) log_status(STATUS_FATAL_ERROR, "Fonts failed to allocate memory");
    if (self->sprites == NULL) log_status(STATUS_FATAL_ERROR, "Sprites failed to allocate memory");
}

void _application_quit(app* self)
{
    for (int i = 0; i > self->sprites_count; i++)
    {
        unload_sprite(&self->sprites[i]);
    }
    
    for (int i = 0; i > self->fonts_count; i++)
    {
        unload_font(self->fonts[i]);
    }

    MZ_FREE(self->sprites);
    MZ_FREE(self->fonts);
    
    QuitMuzzle(self->applet);
}

int _application_add_font(app* self, const char* font_name)
{
    // Checks if have enough space
    if (self->fonts_count >= self->fonts_max)
    {
        self->fonts_max += APPLICATION_FONT_SPRITE_SIZE;
        self->fonts = MZ_REALLOC(self->fonts, sizeof(font) * self->fonts_max);

        if (self->fonts == NULL) log_status(STATUS_FATAL_ERROR, "Fonts failed to allocate memory [realloc]");
    }
    
    char font_path[512];
    sprintf(font_path, "../assets/fonts/%s.ttf", font_name);
    
    self->fonts[self->fonts_count] = load_font(font_path, font_name);
    self->fonts_count++;
    
    return self->fonts_count - 1;
}

int _application_add_sprite(app* self, const char* sprite_name)
{
    // Checks if have enough space
    if (self->sprites_count >= self->sprites_max)
    {
        self->sprites_max += APPLICATION_FONT_SPRITE_SIZE;
        self->sprites = MZ_REALLOC(self->sprites, sizeof(sprite) * self->sprites_max);

        if (self->sprites == NULL) log_status(STATUS_FATAL_ERROR, "Sprites failed to allocate memory [realloc]");
    }
    
    char sprite_path[512];
    sprintf(sprite_path, "../assets/sprites/%s.png", sprite_name);

    self->sprites[self->sprites_count] = load_sprite(sprite_path);
    self->sprites_count++;

    return self->sprites_count - 1;
}

struct _application application(const char* title, int width, int height)
{
    return (struct _application)
    {
        .applet = {0},
        .initialize = _application_initialize,
        .quit = _application_quit,
        .update = _application_update,
        .title = title,
        .width = width,
        .height = height,
        .fonts_max = 0,
        .fonts_count = 0,
        .fonts = NULL,
        .sprites_max = 0,
        .sprites_count = 0,
        .sprites = NULL,
        .add_sprite = _application_add_sprite,
        .add_font = _application_add_font
    };
}