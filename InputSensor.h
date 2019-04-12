#ifndef InputSensor_h
#define InputSensor_h

#include "Arduino.h"
#include "Filters.h"

class InputSensor{

  public:    
    InputSensor(uint8_t analogPin, uint16_t lowLimit, uint16_t highLimit, float freqFilt);
    uint16_t GetValue(void);         // 0-1000   0-100.0%
    void SetValue(uint16_t val);
    uint16_t GetValueFiltered(void); // 0-1000   0-100.0%
    uint8_t  InRange(void);
    void     Cyclic(void);

  private:
    FilterOnePole sensorFilter;
    uint16_t sensorValue;
    uint16_t rawValue;
    uint16_t debugValue;
    uint16_t logicLimitLow;
    uint16_t logicLimitHigh;
    uint8_t  sensorPin;
};

#endif
