#include "user.h"
// #include <Arduino.h>
// #include <EEPROM.h>
#include <M5Core2.h>

struct User current_user = {0}; 
int current_status = SCANNING; 
SemaphoreHandle_t  xCountingSemaphore;

struct User users[3] = {
    {0, 0, 0}, 
    {1, 0, 0},
    {2, 0, 0}
};

int update_user(int user_index) 
{
    if (user_index < 0 || user_index > MAX_USER) {
        return INCORRECT_USER_INDEX; 
    }

    // users[user_index].num_times = users[user_index].num_times + 15;
    // users[user_index].words_learnt = users[user_index].words_learnt + 2;

    // int arr[6] = {
    //     users[0].num_times, users[0].words_learnt,
    //     users[1].num_times, users[1].words_learnt,
    //     users[2].num_times, users[2].words_learnt
    // };

    // for (int i = 0; i < 6; i++) {
    //     EEPROM.writeByte(i, arr[i]);
    // }

    // for (int i = 0; i < 6; i++) {
    //     Serial.printf("%d\n\r", EEPROM.readByte(i));       
    // }    

    current_user = users[user_index];
    current_user.num_times = current_user.num_times + 1; 

    return 0;
}


int init_users(void) 
{
    // int size = sizeof(users);
    // if (!EEPROM.begin(6)) {  
    //     delay(1000000);
    //     return 0;
    // }

    // uint8_t arr[6] = {0, 0, 0, 0, 0, 0};


    // for (int i = 0; i < 6; i++) {
    //     arr[i] = EEPROM.readByte(i);       
    // }

    // users[0].num_times = arr[0]; 
    // users[0].words_learnt = arr[1];   

    // users[1].num_times = arr[2]; 
    // users[1].words_learnt = arr[3]; 
    
    // users[2].num_times = arr[4];  
    // users[2].words_learnt = arr[5];                
  
    // for (int i = 0; i < 3; i++) {
    //     Serial.printf("%d :: %d, %d\n\r", users[i].index, users[i].num_times, users[i].words_learnt);
    // }

    return 1; 
}