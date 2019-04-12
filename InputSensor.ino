
#include "InputSensor.h"


InputSensor::InputSensor(uint8_t analogPin, uint16_t lowLimit, uint16_t highLimit, float freqFilt):
sensorFilter( LOWPASS, freqFilt )
{
    sensorValue = 0;
    sensorPin = analogPin; 
    logicLimitLow = lowLimit;
    logicLimitHigh = highLimit;
    debugValue  = 0;
}

uint16_t InputSensor::GetValueFiltered(void)
{
   #if defined(DEBUG_DISABLE_HW_INPUTS_CHECK)
   return(debugValue);
   #else
   return((uint16_t)sensorFilter.output());
   #endif
}

uint16_t InputSensor::GetValue(void)
{
  #if defined(DEBUG_DISABLE_HW_INPUTS_CHECK)
  return(debugValue);
  #else
  return(sensorValue);
  #endif
    
}

void InputSensor::SetValue(uint16_t val)
{
    debugValue = val;
}

uint8_t InputSensor::InRange(void)
{
    uint8_t result = false;
    
    if ((rawValue > logicLimitLow) && (rawValue < logicLimitHigh))
    {
      result = true;
    }
    return(result);
}

void InputSensor::Cyclic(void)
{
    rawValue = analogRead(sensorPin);
    /* check if data is valid, within range, if not assume error
       and report minim (for example cable break) */
    if ((rawValue < logicLimitLow) || (rawValue > logicLimitHigh)){
      sensorValue = 0;
    }
    else{
      /* Remap sensor value to report 0.0% to 100.0% */
      sensorValue = map(rawValue, logicLimitLow, logicLimitHigh, 0, MAX_REQUEST_100XCENT);
    }
    sensorFilter.input( sensorValue );
}
