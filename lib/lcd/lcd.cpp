#include <M5Core2.h>
#include "lcd.h"


void introduction_display(void * parameter ) 
{
    int i = 0; 
    M5.begin();                //Init M5Core2.  初始化 M5Core2
    
    M5.Lcd.fillScreen(BLUE);
    M5.Lcd.setCursor(50, 50);  //Move the cursor position to (x,y).  移动光标位置到 (x,y)处
    M5.Lcd.setTextColor(ORANGE);  //Set the font color to white.  设置字体颜色为白色
    M5.Lcd.setTextSize(2);  //Set the font size.  设置字体大小
  
    // for(;;) 
    // {
    //     // M5.lcd.clear();
    //     // M5.Lcd.fillScreen(LIGHTGREY);
    //     // M5.Lcd.printf("%d", i++);
    //     // M5.Lcd.setCursor(10, 10);  //Move the cursor position to (x,y).  移动光标位置到 (x,y)处
    //     // M5.Lcd.setTextColor(WHITE);  //Set the font color to white.  设置字体颜色为白色
    //     // M5.Lcd.setTextSize(1);  //Set the font size.  设置字体大小
    //     // M5.Lcd.printf("Display Test!");  //Serial output format string.  输出格式化字符串
    //     // M5.update();  //Read the press state of the key.  读取按键 A, B, C 的状态
    //     Serial.printf("Test... %i", i);
    //     vTaskDelay(500);  
               
    // }
}