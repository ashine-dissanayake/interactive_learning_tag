// /*
// *******************************************************************************
// * Copyright (c) 2021 by M5Stack
// *                  Equipped with M5Core2 sample source code
// *                          配套  M5Core2 示例源代码
// * Visit for more information: https://docs.m5stack.com/en/core/core2
// * 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/core2
// *
// * Describe: Display Example.  显示屏示例
// * Date: 2021/7/21
// *******************************************************************************
// */
// #include <Arduino.h>
// // #include <Queue.h>
// #include <M5Core2.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>

// typedef struct Message {
//   int count;
// } Message;

// static QueueHandle_t msg_queue;
// static const int msg_queue_len = 10;     // Size of msg_queue

// void task1(void* parameters) {
//   Message rcv_msg;
//   M5.begin(); 
//   M5.Lcd.fillScreen(LIGHTGREY);
//   M5.Lcd.setTextColor(
//       RED);  //Set the font color to white.  设置字体颜色为白色
//   M5.Lcd.setTextSize(2);  //Set the font size.  设置字体大小
//   M5.Lcd.printf("Display Test!");  //Serial output format string.  输出格式化字符串

//   for(;;) {
//     if (xQueueReceive(msg_queue, (void *)&rcv_msg, 0) == pdTRUE) {
//       M5.Lcd.clearDisplay(LIGHTGREY);
//       M5.Lcd.setCursor(
//           10, 10);  //Move the cursor position to (x,y).  移动光标位置到 (x,y)处      
//       M5.Lcd.printf("Display Test!: %i", rcv_msg.count);  //Serial output format string.  输出格式化字符串
//     }    
//     vTaskDelay(1000 / portTICK_PERIOD_MS); 
//   }
// }


// void task2(void* parameters) {
//   Message msg;
//   int counter = 0;

//   for(;;) {
//     // Serial.print("Task 2 Counter"); 
//     // Serial.println(counter2++);
//     msg.count = counter; 
//     xQueueSend(msg_queue, (void *) &msg, 10);    
//     counter++;
     
//     vTaskDelay(1000 / portTICK_PERIOD_MS); 
//   }
// }

// void setup() {
//   // Serial.begin(115200);
//   msg_queue = xQueueCreate(msg_queue_len, sizeof(Message));

//   xTaskCreate(
//     task1, 
//     "Task 1", 
//     3000, 
//     NULL, 
//     1, 
//     NULL
//   ); 

//   xTaskCreate(
//     task2, 
//     "Task 2", 
//     1000, 
//     NULL, 
//     2, 
//     NULL
//   );   

// }


// void loop() { 
//   // ignore
// }


/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; //In seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      if (strcmp("IDTILL", advertisedDevice.getName().c_str()) == 0) {
        Serial.printf("Name: %s :: UUID: %s --> %d\n\r", advertisedDevice.getName().c_str(), advertisedDevice.getAddress().toString().c_str(), advertisedDevice.getRSSI());
      }
      
      // Serial.printf("\n\r");
      // Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);
}