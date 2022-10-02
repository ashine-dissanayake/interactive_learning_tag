#include <M5Core2.h>
#include "touch.h"
#include "../user/user.h"

int current_ui = SCANNING; 
// SemaphoreHandle_t xCountingSemaphore;

void touch_task(void* parameters)
{
    xCountingSemaphore = xSemaphoreCreateCounting(1,1);

    for(;;) 
    {
        TouchPoint_t pos = M5.Touch.getPressPoint();  // Stores the touch coordinates in pos.
        Serial.printf("x=%d AND y=%d\n\r", pos.x, pos.y);

        switch (current_ui)
        {
        case SCANNING: 
            if (pos.x >= 80 && pos.x <= 100 && pos.y > 250) 
            {
                current_ui = INFO_UI; 
                xSemaphoreGive(xCountingSemaphore);                
            } else if (pos.x >= 160 && pos.x <= 200 && pos.y > 250) 
            {
                current_ui = SETTING_UI; 
                xSemaphoreGive(xCountingSemaphore);                
            } else if (pos.x >= 240 && pos.x <= 290 && pos.y > 250) 
            {
                current_ui = POWER_DOWN; 
                xSemaphoreGive(xCountingSemaphore);                
            }
            break;
        case MAIN_UI:
            if (pos.x > -1 && pos.x <= 60 && pos.y > -1 && pos.y <= 60) 
            {
                current_ui = USER_UI; 
                xSemaphoreGive(xCountingSemaphore);                
            } else if (pos.x >= 80 && pos.x <= 100 && pos.y > 250) 
            {
                current_ui = INFO_UI; 
                xSemaphoreGive(xCountingSemaphore);                
            } else if (pos.x >= 160 && pos.x <= 200 && pos.y > 250) 
            {
                current_ui = SETTING_UI; 
                xSemaphoreGive(xCountingSemaphore);                
            } else if (pos.x >= 240 && pos.x <= 290 && pos.y > 250) 
            {
                current_ui = POWER_DOWN; 
                xSemaphoreGive(xCountingSemaphore);                
            }
            break;
        case USER_UI: 
            if (pos.y >= 190) {
                current_ui = MAIN_UI;
                xSemaphoreGive(xCountingSemaphore);                
            }
            break;
        case SETTING_UI: 
            if (pos.y >= 190 && pos.y <= 220) 
            {
                if (current_status == LEARNING) 
                {
                    current_ui = MAIN_UI;
                } else { 
                    current_ui = SCANNING; 
                }        
                xSemaphoreGive(xCountingSemaphore);
            } 
            break;  
        case DISCONNECT_UI: 
            break;                        
        case INFO_UI: 
            if (pos.y >= 190 && pos.y <= 220) 
            {
                if (current_status == LEARNING) 
                {
                    current_ui = MAIN_UI;
                } else { 
                    current_ui = SCANNING; 
                }        
                xSemaphoreGive(xCountingSemaphore);
            } 
            break;          
        }
        
        vTaskDelay(500);                
    }
}