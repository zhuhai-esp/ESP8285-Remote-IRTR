#include "ConfigWifi.h"
#include <Arduino.h>
#include <IRac.h>

IRrecv irrecv(14, 1024, 50, true);
decode_results results;

void setup() {
  configWifi();
  irrecv.setUnknownThreshold(12);
  irrecv.setTolerance(25);
  irrecv.enableIRIn();
}

void loop() {
  ArduinoOTA.handle();
  if (irrecv.decode(&results)) {
    Serial.print(resultToHumanReadableBasic(&results));
    String description = IRAcUtils::resultAcToString(&results);
    if (description.length()) {
      Serial.println(D_STR_MESGDESC ": " + description);
    }
  }
}