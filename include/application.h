#ifndef UJER_EATS_APPLICATION_H
#define UJER_EATS_APPLICATION_H

#define APPLICATION_FONT_SPRITE_SIZE 10

#include <Muzzle.h>

typedef struct _application
{
    void (*initialize)(struct _application*);
    void (*update)(struct _application*);
    void (*quit)(struct _application*);
    
    Applet applet;
    font* fonts;
    sprite* sprites;
    size_t fonts_count;
    size_t sprites_count;
    size_t fonts_max;
    size_t sprites_max;
    
    int (*add_font)(struct _application*, const char*);
    int (*add_sprite)(struct _application*, const char*);
    
    const char* title;
    int width;
    int height;
} app;

void _application_initialize(app* self);
void _application_update(app* self);
void _application_quit(app* self);

int _application_add_font(app* self, const char* font_name);
int _application_add_sprite(app* self, const char* sprite_name);

app application(const char* title, int width, int height);

#endif //UJER_EATS_APPLICATION_H