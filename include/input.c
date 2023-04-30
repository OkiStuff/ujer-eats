#include "input.h"

int safe_key_press(safe_input_manager* manager, int key)
{
    if (key_down(manager->applet, key) && manager->key_pressed == 0)
    {
        manager->key_pressed = 1;
        return 1;
    }
    
    if (key_up(manager->applet, key) && manager->key_pressed == 1)
    {
        manager->key_pressed = 0;
    }
    
    return 0;
}

int safe_mouse_down(safe_input_manager* manager, int button)
{
    if (mouse_down(manager->applet, button) && manager->mouse_pressed == 0)
    {
        manager->mouse_pressed = 1;
    }
    
    if (mouse_up(manager->applet, button) && manager->mouse_pressed == 1)
    {
        manager->mouse_pressed = 0;
        return 1;
    }
    
    return 0;
}