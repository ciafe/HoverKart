#ifndef DisplayInfo_h
#define DisplayInfo_h

#include "Arduino.h"

class DisplayInfo{

  public:
    typedef enum
    {
      DISPLAY_KEY_ON_ERROR = 0x00,
      DISPLAY_KEY_OFF      = 0x01,
      DISPLAY_RUNNING      = 0x02,
      SENSOR_INIT          = 0x03,
      DISPLAY_INIT         = 0x04,     
      SENSOR_ACC_ERROR     = 0x05,
      SENSOR_BRAKE_ERROR   = 0x06
    } DisplayInfosType;
    
    DisplayInfo(void);
    uint8_t Init(void);
    void Update(void); 
    void Message(uint8_t type);

  private:  
    uint8_t  current_state;
    uint8_t  split_tasks;
    uint8_t  state_entry;
    
};

#endif
