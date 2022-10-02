#ifndef _USER_H
#define _USER_H

#define INCORRECT_USER_INDEX    1
#define MAX_USER                3  

#define SCANNING                0 
#define LEARNING                1
#define POWER_DOWN              6

#include <Arduino.h>
#include <freertos/FreeRTOS.h>

struct User
{
    int index; 
    int num_times; 
    int words_learnt; 
};

extern int current_status; 
extern struct User current_user; 
extern struct User users[3];
extern SemaphoreHandle_t  xCountingSemaphore;

int update_user(int user_index);
int init_users(void);
#endif