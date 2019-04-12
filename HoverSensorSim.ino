
#include "HoverSensorSim.h"


HoverSensorSim::HoverSensorSim(uint8_t pinRx, uint8_t pinTx, uint16_t baud, uint16_t lm):
serialSensor(pinRx, pinTx)
{
    limitAccel=lm;
    if(limitAccel > HoverSensorSim::LIMIT_MAX) limitAccel = HoverSensorSim::LIMIT_MAX;
    serialSensor.begin(baud);
}

uint16_t HoverSensorSim::GetSensorLimit(void)
{
  return(limitAccel);
}

void HoverSensorSim::Init(void){
  
  /* Init frame sent by the sensor with diferent header */
  #if defined(HOVER_SENSOR_V2)
  serialSensor.write9(0x100);
  #else
  serialSensor.write9(0x10F);
  #endif
  serialSensor.write9(0x000);
  serialSensor.write9(0x000);
  serialSensor.write9(0x000);
  serialSensor.write9(0x000);
  serialSensor.write9(HoverSensorSim::PRESENCE_OPEN);
  serialSensor.write9(0x58);
  serialSensor.write9(0x58);
  #if defined(HOVER_SENSOR_V2)
  serialSensor.write9(0x00);
  serialSensor.write9(0x00);
  #endif
}

void HoverSensorSim::Transmit(int accel, int sensorPos){
  uint8_t sp[2];
  sp[0]=(accel >> 8) & 0xFF;
  sp[1]=accel & 0xFF;

  serialSensor.write9(0x100);
  serialSensor.write9(sp[1]);
  serialSensor.write9(sp[0]);
  serialSensor.write9(sp[1]);
  serialSensor.write9(sp[0]);
  serialSensor.write9(sensorPos);
  serialSensor.write9(0x58);
  serialSensor.write9(0x58);
  #if defined(HOVER_SENSOR_V2)
  serialSensor.write9(0x00);
  serialSensor.write9(0x00);
  #endif
}
