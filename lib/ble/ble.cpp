#include <Arduino.h>
#include <M5Core2.h>

#include "ble.h"
#include "../user/user.h"
#include "../touch/touch.h"


int scanTime = 5; //In seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks 
{
    void onResult(BLEAdvertisedDevice advertisedDevice) 
    {
        if (strstr(advertisedDevice.getName().c_str(), "IDTILL") != 0 
            && advertisedDevice.getRSSI() >= -50) 
        { 
            if (update_user(advertisedDevice.getName().c_str()[7] - '0') == 0) {
                current_status = LEARNING; 
                current_ui = MAIN_UI;
                xSemaphoreGive(xCountingSemaphore);                                
            }
            Serial.printf("Name: %s :: Address: %s --> %d\n\r", advertisedDevice.getName().c_str(), advertisedDevice.getAddress().toString().c_str(), advertisedDevice.getRSSI());
        }
    }
};


// bool is_new_user(BLEAdvertisedDevice user) {
    // for (int i = 0; i < num_user; i++) {
    //     if (user.getAddress().equals(users[i].getAddress())) {
    //         return false; 
    //     }
    // }
    // return true; 
// }


/**
 * 
 */
void ble_setup() 
{ 
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);  // less or equal setInterval value
}


/**
 * 
 */ 
void ble_task(void* parameters)
{
    ble_setup(); 

    for(;;)
    {
        // put your main code here, to run repeatedly:
        if (current_status == SCANNING) {
            BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
            Serial.print("Devices found: ");
            Serial.println(foundDevices.getCount());
            Serial.println("Scan done!");
            pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
        } 
        Serial.printf("CURRENT STATUS INDEX: %d\n\r", current_status);
        vTaskDelay(2000 / portTICK_PERIOD_MS); 
    } 
}