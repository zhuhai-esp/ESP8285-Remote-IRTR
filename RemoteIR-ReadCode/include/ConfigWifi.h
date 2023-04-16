#ifndef __CONFIG_WIFI_H__
#define __CONFIG_WIFI_H__

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>

void inline configWifi() {
  Serial.begin(115200);
  Serial.println("\nESP8285 Start Wifi Connect!");
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  // 检查网络状态，等待连接
  for (int i = 0; WiFi.status() != WL_CONNECTED && i < 50; i++) {
    delay(200);
  }
  if (WiFi.status() != WL_CONNECTED) {
    // 开启配网模式
    WiFi.beginSmartConfig();
    for (int i = 0;; i++) {
      // 等待配网成功
      if (WiFi.smartConfigDone()) {
        Serial.println();
        break;
      }
      delay(500);
      // 红绿交替慢闪
      Serial.print(".");
    }
  }
  delay(1000);
  WiFi.mode(WIFI_STA);
  Serial.printf("IP: %s\n", WiFi.localIP().toString().c_str());
  ArduinoOTA.begin();
}

#endif