#ifndef _BLE_H
#define _BLE_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

/** External Variables */
// Number of current users using the tag.

/** External Functions */ 
extern void ble_task(void* parameters); 
bool is_new_user(BLEAdvertisedDevice user);

#endif