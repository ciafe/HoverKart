#ifndef HoverMotor_h
#define HoverMotor_h

#include "Arduino.h"
#include "HoverSensorSim.h"

class HoverMotor{

  public:
    typedef enum
    {
      FORWARD  = 0x00,
      REVERSE  = 0x01
    } MotorDirectionType;
    HoverMotor(uint8_t pinRx, uint8_t pinTx);
	  /* DANGER!!! DO NOT change direction with power > 0, main board can be damaged!!! */
    void SetPower(uint16_t power, uint8_t direction); // collect a new power request, 0-1000, 0-100.0%
    void Cyclic(void);
    void Enable(void); 
    void Disable(void); 

  private:   
    typedef enum
    {
      MOTOR_DELAY_INIT = 0x00,
      MOTOR_INIT       = 0x01,
      MOTOR_DISABLED   = 0x02,
      MOTOR_ENABLED    = 0x03
    } HoverSMotorStateType;
    
    HoverSensorSim simSensor;
    uint16_t current_power;
    uint8_t  current_direction;
    int      current_request;
    uint8_t  current_state;
    uint8_t  request_state;
    uint32_t init_time;
};

#endif
