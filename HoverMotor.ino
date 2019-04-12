
#include "HoverMotor.h"
#include "Config.h"


HoverMotor::HoverMotor(uint8_t pinRx, uint8_t pinTx):
simSensor(pinRx, pinTx, BAUD_RATE_HOVER_SENSOR , HOVER_SENSOR_SIM_MAX_VALUE)
{
    current_power = 0;
    current_direction = HoverMotor::FORWARD;
    current_request = 0;
    current_state = HoverMotor::MOTOR_DELAY_INIT;
    request_state = HoverMotor::MOTOR_DELAY_INIT;
    init_time = millis();
}

void HoverMotor::Enable(void)
{
  request_state = HoverMotor::MOTOR_ENABLED;
}

void HoverMotor::Disable(void)
{
  request_state = HoverMotor::MOTOR_DISABLED;
}

void HoverMotor::SetPower(uint16_t power, uint8_t direction)
{
    if (power <= MAX_REQUEST_100XCENT){
      current_power = power;
    }
    else{
      current_power = MAX_REQUEST_100XCENT;
    }
    current_direction = direction;

    int sensordata = map(current_power, 0, MAX_REQUEST_100XCENT,  0, simSensor.GetSensorLimit());
    if (current_direction == HoverMotor::FORWARD){
      current_request = sensordata;
    }
    else{
      current_request = sensordata * -1;
    }
}

void HoverMotor::Cyclic(void)
{
  uint32_t current_time;
	  
  switch (current_state)
  {
    case HoverMotor::MOTOR_DELAY_INIT:
      current_time = millis();
      if ((current_time - init_time) > 500){ /* startup delay without transmission data */
        current_state = HoverMotor::MOTOR_INIT;
      }
    break;
    
    case HoverMotor::MOTOR_INIT:
      simSensor.Init();
      simSensor.Init();
      current_state = HoverMotor::MOTOR_DISABLED;
    break;
    
    case HoverMotor::MOTOR_DISABLED:
      simSensor.Transmit(0, HoverSensorSim::PRESENCE_OPEN);

      if (request_state == HoverMotor::MOTOR_ENABLED){
        current_state = HoverMotor::MOTOR_ENABLED;
      }
    break;
    
    case HoverMotor::MOTOR_ENABLED:
      simSensor.Transmit(current_request, HoverSensorSim::PRESENCE_CLOSED);
      //Serial.println(current_request);
      
      if (request_state == HoverMotor::MOTOR_DISABLED){
        current_state = HoverMotor::MOTOR_DISABLED;
      }
    break;

    default:
      current_state = HoverMotor::MOTOR_INIT;
    break;
  }
  
}
