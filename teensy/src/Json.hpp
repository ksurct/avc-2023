#ifndef __JSON_HPP__
#define __JSON_HPP__
#include <ArduinoJson.h>

namespace json {
    struct Data {
        Data();
        float fr_data;
        float fl_data;
        float f_data;
        float l_data;
        float r_data;
        float accelX;
        float accelY;
        float accelZ;
        float magX;
        float magY;
        float magZ;
        float gyroX;
        float gyroY;
        float gyroZ;
        float yaw;
        void sendJson();
    };
}



#endif
