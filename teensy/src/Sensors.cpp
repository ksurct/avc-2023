#include "Sensors.hpp"
#include "Json.hpp"

using namespace json;
static json::Data *data;

IntervalTimer timer;
unsigned long echoFRTime;
unsigned long echoRTime;
unsigned long echoLTime;
unsigned long echoFLTime;
unsigned long echoFTime;
float normX;
float normY;
float normZ;

//Adafruit_FXAS21002C gyroscope = Adafruit_FXAS21002C(0x0021002C); 
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

/*
class magnet
{
  float x_hard = -33.77;
  float y_hard = -99;
  float z_hard = -197.1;
  float soft[3][3] = {
      {1.095, -0.017, 0.003},
      {0.016, 1.013, 0.061},
      {0.000, 0.062, 0.903}};

  /*
    magnet(){
      x_hard = -8.07;
      y_hard = -26.33;
      z_hard = -67.37;
      soft = {
        { 0.984, -0.3, 0.012 },
        { -0.032, 1.014, 0.045 },
        { 0.013, 0.042, 1.01 }
      };
    }
    
public:
  void calc(float x, float y, float z, float &xout, float &yout, float &zout)
  {
    float xtemp = x - x_hard;
    float ytemp = y - y_hard;
    float ztemp = z - z_hard;

    xout = soft[0][0] * xtemp + soft[0][1] * ytemp + soft[0][2] * ztemp;
    yout = soft[1][0] * xtemp + soft[1][1] * ytemp + soft[1][2] * ztemp;
    zout = soft[2][0] * xtemp + soft[2][1] * ytemp + soft[2][2] * ztemp;
  }
};
*/

struct calibration
{
  float magx = -12.85;
  float magy = -33.8;
  float magz = -74.6;
  float gyrox = -0.0127;
  float gyroy = 0.00545;
  float gyroz = 0.0098;
};

struct sensor{
  float x;
  float y;
  float z;
};

struct euler{
  float yaw;
  float pitch;
  float roll;
};

// magnet tune;

void sensorsInit(Data *dataReference)
{
  pinMode(trigPinF1, OUTPUT);
  pinMode(trigPinF2, OUTPUT);
  pinMode(trigPinF3, OUTPUT);
  pinMode(trigPinF4, OUTPUT);
  pinMode(trigPinF5, OUTPUT);
  timer.begin(sensorTrigger, 150000);
  attachInterrupt(echoPinF1, frReceived, CHANGE);
  attachInterrupt(echoPinF2, rReceived, CHANGE);
  attachInterrupt(echoPinF3, lReceived, CHANGE);
  attachInterrupt(echoPinF4, flReceived, CHANGE);
  attachInterrupt(echoPinF5, fReceived, CHANGE);
  // attachInterrupt(echaevent.acceleration.xoPinF5, fReceived, CHANGE);
  data = dataReference;

  // mag_offset.x = -8.28;
  // mag_offset.y = -26.74;
  // mag_offset.z = -67.09;

  if (!accelmag.begin())
  {
    /* There was a problem detecting the FXOS8700 ... check your connections */
  }
  setNorm();
}

void setNorm()
{
  sensors_event_t aevent, mevent;

  // /* Get a new sensor event */
  accelmag.getEvent(&aevent, &mevent);

  normX = aevent.acceleration.x;
  normY = aevent.acceleration.y;
  normZ = aevent.acceleration.z;
}

void getAccelData()
{
  sensors_event_t aevent, mevent, gevent;

  /* Get a new sensor event */
  accelmag.getEvent(&aevent, &mevent);
  //gyroscope.getEvent(&gevent);

  calibration cal;

  sensor accel = {aevent.acceleration.x, aevent.acceleration.x, aevent.acceleration.x};
  sensor mag = {mevent.magnetic.x - cal.magx, mevent.magnetic.y - cal.magy, mevent.magnetic.z - cal.magz};
  //sensor gyro = {gevent.gyro.x - cal.gyrox, gevent.gyro.y - cal.gyroy, gevent.gyro.z - cal.gyroz};

  data->accelX = accel.x;
  data->accelY = accel.y;
  data->accelZ = accel.z;

  //data->gyroX = gyro.x;
  //data->gyroY = gyro.y;
  //data->gyroZ = gyro.z;

  data->magX = mag.x;
  data->magY = mag.y;
  data->magZ = mag.z;

  euler e;

  // pitch = 180 * atan2(accelX, sqrt(accelY*accelY + accelZ*accelZ))/PI;
  // e.pitch = atan2(accel.x, sqrt(accel.y * accel.y + accel.z * accel.z)) * (180 / PI);
  // roll = 180 * atan2(accelY, sqrt(accelX*accelX + accelZ*accelZ))/PI;
  // e.roll = atan2(accel.y, sqrt(accel.x * accel.x + accel.z * accel.z)) * (180 / PI);

  sensor mag_new;
  

  // mag_x = magReadX*cos(pitch) + magReadY*sin(roll)*sin(pitch) + magReadZ*cos(roll)*sin(pitch)
  // mag_new.x = mag.x * cos(e.pitch) + mag.y * sin(e.roll) * sin(e.pitch) + mag.z * cos(e.roll) * sin(e.pitch); 
  // mag_y = magReadY * cos(roll) - magReadZ * sin(roll)
  // mag_new.y = mag.y * cos(e.roll) - mag.z * sin(e.roll);
  
   e.yaw = atan2(mag.x, mag.y) * (180/PI);
  //e.yaw = atan2(mag_new.x, mag_new.y) * (180 / PI);

  //tune.calc(mevent.magnetic.x, mevent.magnetic.y, mevent.magnetic.z, data->magX, data->magY, data->magZ);

  data->yaw = e.yaw; // don't use
}

void sensorTrigger()
{
  digitalWriteFast(trigPinF1, LOW);
  digitalWriteFast(trigPinF2, LOW);
  digitalWriteFast(trigPinF3, LOW);
  digitalWriteFast(trigPinF4, LOW);
  digitalWriteFast(trigPinF5, LOW);
  delayMicroseconds(2);
  digitalWriteFast(trigPinF1, HIGH);
  digitalWriteFast(trigPinF2, HIGH);
  digitalWriteFast(trigPinF3, HIGH);
  digitalWriteFast(trigPinF4, HIGH);
  digitalWriteFast(trigPinF5, HIGH);
  delayMicroseconds(10);
  digitalWriteFast(trigPinF1, LOW);
  digitalWriteFast(trigPinF2, LOW);
  digitalWriteFast(trigPinF3, LOW);
  digitalWriteFast(trigPinF4, LOW);
  digitalWriteFast(trigPinF5, LOW);
}

void frReceived()
{
  if (digitalReadFast(echoPinF1))
  { // HIGH
    echoFRTime = micros();
  }
  else
  {
    data->fr_data = (micros() - echoFRTime) * .034 / 200.0;
    if (data->fr_data > 10)
    {
      data->fr_data = -1;
    }
  }
}

void rReceived()
{
  if (digitalReadFast(echoPinF2))
  { // HIGH
    echoRTime = micros();
  }
  else
  {
    data->r_data = (micros() - echoRTime) * .034 / 200.0;
    if (data->r_data > 10)
    {
      data->r_data = -1;
    }
  }
}

void lReceived()
{
  if (digitalReadFast(echoPinF3))
  { // HIGH
    echoLTime = micros();
  }
  else
  {
    data->l_data = (micros() - echoLTime) * .034 / 200.0;
    if (data->l_data > 10)
    {
      data->l_data = -1;
    }
  }
}

void flReceived()
{
  if (digitalReadFast(echoPinF4))
  { // HIGH
    echoFLTime = micros();
  }
  else
  {
    data->fl_data = (micros() - echoFLTime) * .034 / 200.0;
    if (data->fl_data > 10)
    {
      data->fl_data = -1;
    }
  }
}

void fReceived()
{
  if (digitalReadFast(echoPinF5))
  { // HIGH
    echoFTime = micros();
  }
  else
  {
    data->f_data = (micros() - echoFTime) * .034 / 200.0;
    if (data->f_data > 10)
    {
      data->f_data = -1;
    }
  }
}

// int sensorDataFunction(int sizeOfDistances, int epin, int tpin){

// long duration1; // variable for the duration of sound wave travel
// int distance1; // variable for the distance measurement

//  int distance[sizeOfDistances];
//   for(int i = 0; i < sizeOfDistances; i++){
//   digitalWriteFast(tpin, LOW);
//   delayMicroseconds(2);
//   // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
//   digitalWriteFast(tpin, HIGH);
//   delayMicroseconds(1);
//   digitalWriteFast(tpin, LOW);
//   // Reads the echoPin, returns the sound wave travel time in microseconds
//   // Calculating the distance
//   distance[i] = pulseIn(epin, HIGH, 3000) * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
//   // Displays the distance on the Serial Monitor
//   }
//   int average = 0;
//   int elements = 0;
//   for(int i = 0; i < sizeOfDistances; i++){
//     if(distance[i] <= 200 && distance[i] != 0){
//       average += distance[i];
//       elements++;
//     }
//   }
//   if(elements != 0){
//     average = average / elements;
//     return average;
//   }else{
//     return -1;
//   }
// }

// void updateSensorData(int sizeOfDistances){
//   // data.fr_data = sensorDataFunction(sizeOfDistances, echoPinF1, trigPinF1);
//   // data.r_data = sensorDataFunction(sizeOfDistances, echoPinF2, trigPinF2);
//   // data.l_data = sensorDataFunction(sizeOfDistances, echoPinF3, trigPinF3);
//   // data.fl_data = sensorDataFunction(sizeOfDistances, echoPinF4, trigPinF4);
//   data.f_data = sensorDataFunction(sizeOfDistances, echoPinF5, trigPinF5);
// }