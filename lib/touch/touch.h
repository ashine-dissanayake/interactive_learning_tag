#ifndef _TOUCH_H
#define _TOUCH_H

#define MAIN_UI         2
#define USER_UI         3
#define SETTING_UI      4
#define DISCONNECT_UI   5
#define INFO_UI         7

extern int current_ui; 
// extern SemaphoreHandle_t xCountingSemaphore;

void touch_task(void* parameters);

#endif