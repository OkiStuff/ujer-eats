#ifndef UJER_EATS_INPUT_H
#define UJER_EATS_INPUT_H

#include <Muzzle.h>
#include <stddef.h>

typedef struct _safe_input_manager
{
    uint32_t key_pressed;
    uint32_t mouse_pressed;
    Applet* applet;
} safe_input_manager;

int safe_key_press(safe_input_manager* manager, int key);
int safe_mouse_press(safe_input_manager* manager, int button);

#endif //UJER_EATS_INPUT_H