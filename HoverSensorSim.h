#ifndef HoverSensorSim_h
#define HoverSensorSim_h

#include "Arduino.h"
#include <SoftwareSerial9.h>

class HoverSensorSim{

  public:
    typedef enum
    {
      PRESENCE_CLOSED  = 0x55,
      PRESENCE_OPEN    = 0xAA
    } SensorPresenceType;

    HoverSensorSim(uint8_t pinRx, uint8_t pinTx, uint16_t baud, uint16_t lm);
    void Init(void);
    void Transmit(int accel, int sensorPos);
	uint16_t GetSensorLimit(void);

  private:
    typedef enum
    {
      LIMIT_MAX  = 5000,
      LIMIT_MIN  = 0000
    } SensorValueLimits;
	
    SoftwareSerial9 serialSensor;
    int limitAccel;
    uint16_t speed;
};

#endif
