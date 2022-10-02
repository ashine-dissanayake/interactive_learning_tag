#include <M5Core2.h>
#include "lcd.h"
#include "../user/user.h"
#include "../touch/touch.h"

void draw_icon(int x, int y) 
{
    M5.Lcd.fillRect(x, y, 50, 55, DARKGREY);  
    M5.Lcd.fillCircle(x + 25, y + 18, 15, BLACK); 
    M5.Lcd.fillRoundRect(x + 2, y + 33, 46, 20, 5, BLACK);
}


void draw_language_box(String language) 
{
    M5.Lcd.setCursor(100, 20);
    M5.Lcd.fillRect(100, 0, 180, 55, GREENYELLOW);  
    M5.Lcd.printf("%s", language);
}


void draw_power_button() 
{
    M5.Lcd.fillCircle(260, 210, 25, RED);  
    M5.Lcd.fillCircle(260, 210, 15, WHITE);  
    M5.Lcd.fillCircle(260, 210, 10, RED);  
    M5.Lcd.fillRoundRect(258, 190, 5, 25, 5, WHITE);     
}


void draw_menu_button() {
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.fillRoundRect(120, 185, 80, 50, 5, LIGHTGREY); 
    M5.Lcd.setCursor(125, 200);
    M5.Lcd.print("MENU");   
}


void draw_info_button() {
    M5.Lcd.fillCircle(53, 210, 25, BLUE);  
    M5.Lcd.setCursor(46, 200);
    M5.Lcd.setTextColor(WHITE);  
    M5.Lcd.print("i");    
}

void introduction_display(void * parameter ) 
{
    M5.Lcd.fillScreen(PINK);
    M5.Lcd.setTextSize(7);  
    M5.Lcd.setTextColor(BLACK);  
    M5.Lcd.setCursor(60, 100);  
    M5.Lcd.printf("HELLO");
    M5.Lcd.setTextSize(3);  //Set the font size.  设置字体大小
    // Initialise the start ui in the LEARNING STATE. 
    vTaskDelay(2000);        
    String language = "FRENCH";
    for(;;) 
    {
        xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);        
        M5.Lcd.clear(WHITE);
        
        if (current_ui == SCANNING) 
        {
            M5.Lcd.setTextColor(BLACK);  
            M5.Lcd.setTextSize(3);  //Set the font size.  设置字体大小
            M5.Lcd.setCursor(70, 110);  //Move the cursor position to (x,y).  移动光标位置到 (x,y)处 
            M5.Lcd.printf("SCANNING...");  
            draw_info_button(); 
            draw_menu_button();
            draw_power_button(); 

        } else if (current_ui == INFO_UI) 
        {
            M5.Lcd.setCursor(70, 10);
            M5.Lcd.setTextColor(BLUE);  
            M5.Lcd.printf("...INFO...");   
            M5.Lcd.setTextSize(2);  //Set the font size.  设置字体大小

            if (current_status == SCANNING) 
            {
                M5.Lcd.setCursor(0, 50);
                M5.Lcd.printf("To connect to tag, you must create a beacon.");
                M5.Lcd.setCursor(0, 90);            
                M5.Lcd.printf("1. Name beacon IDTILL_i, i is the user index between 0 & 2.");  
                M5.Lcd.setCursor(0, 150);            
                M5.Lcd.printf("2. Walk towards tag with beacon in hand.");              
            } else if (current_status == LEARNING) {
                M5.Lcd.setCursor(0, 50);
                M5.Lcd.printf("For next word, place hand near PIR sensor.");
                M5.Lcd.setCursor(0, 90);            
                M5.Lcd.printf("Menu button to change operating features.");  
                M5.Lcd.setCursor(0, 130);            
                M5.Lcd.printf("User button to check user's statistics.");                  
            }
            M5.Lcd.fillRect(73, 190, 180, 48, RED);               
            M5.Lcd.setTextSize(3);  //Set the font size.  设置字体大小

        } else if (current_ui == MAIN_UI) 
        {
            draw_icon(2, 2);
            M5.Lcd.setTextColor(BLACK);  
            draw_language_box(language);
            M5.Lcd.setCursor(70, 110);
            M5.Lcd.printf("...MAIN...");   
            draw_info_button(); 
            draw_menu_button();
            draw_power_button();                

        } else if (current_ui == USER_UI) 
        { 
            M5.Lcd.setCursor(70, 10);
            M5.Lcd.printf("...USER...");
            M5.Lcd.fillRoundRect(20, 50, 280, 120, 10, LIGHTGREY);
            M5.Lcd.setTextSize(2);  //Set the font size.  设置字体大小          
            M5.Lcd.setCursor(30, 60);
            M5.Lcd.printf("USER NO.          %d", current_user.index + 1);                  
            M5.Lcd.setCursor(30, 100);
            M5.Lcd.printf("NO. TIMES USED.   %d", current_user.num_times);                  
            M5.Lcd.setCursor(30, 140);
            M5.Lcd.printf("WORDS LEARNT      %d", current_user.words_learnt);                  
            M5.Lcd.setTextSize(3);  //Set the font size.  设置字体大小

            M5.Lcd.fillRect(73, 190, 180, 48, RED);               
        
        } else if(current_ui == SETTING_UI) 
        {
            M5.Lcd.setCursor(70, 110);
            M5.Lcd.printf("...MENU...");
            M5.Lcd.fillRect(73, 190, 180, 48, RED);   
        } else if(current_ui == POWER_DOWN) 
        {
            M5.Lcd.fillScreen(DARKCYAN);
            M5.Lcd.setCursor(30, 110);
            M5.Lcd.printf("...POWER OFF...");
            
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);        
    }
}