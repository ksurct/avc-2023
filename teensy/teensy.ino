#include "src/Json.hpp"
#include "src/Sensors.hpp"

json::Data data;

void setup()
{
    Serial.begin(115200);
    sensorsInit(&data);
}

unsigned long time = millis();
unsigned long interval = 5000;
bool constantOut = false;
unsigned long constantOutTimer;
uint16_t constantOutInterval = 200;

void loop()
{
    getAccelData();
    if (Serial.available()){
        while (Serial.available()) {
            Serial.read();
        }
        data.sendJson();
        time += interval;
    }
}



