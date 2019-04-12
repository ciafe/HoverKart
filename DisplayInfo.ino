#include "DisplayInfo.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include "Config.h"

LiquidCrystal_I2C lcd(0x3F,16,2);
time_t time_stored;
uint16_t accel_level_prev;

byte Level7[8] = {
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B00000,
};
byte Level6[8] = {
B00000,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B00000,
};
byte Level5[8] = {
B00000,
B00000,
B11111,
B11111,
B11111,
B11111,
B11111,
B00000,
};
byte Level4[8] = {
B00000,
B00000,
B00000,
B11111,
B11111,
B11111,
B11111,
B00000,
};
byte Level3[8] = {
B00000,
B00000,
B00000,
B00000,
B11111,
B11111,
B11111,
B00000,
};
byte Level2[8] = {
B00000,
B00000,
B00000,
B00000,
B00000,
B11111,
B11111,
B00000,
};
byte carF[8] = {
B00000,
B00000,
B00000,
B00011,
B11111,
B11111,
B00100,
B00000,
};
byte carR[8] = {
B00000,
B00000,
B00000,
B11100,
B11111,
B11111,
B00100,
B00000,
};


DisplayInfo::DisplayInfo()
{
    current_state = DisplayInfo::DISPLAY_INIT;
    state_entry = 0;
    split_tasks = 0;
}

uint8_t DisplayInfo::Init(void)
{
  uint8_t result = false;
  static uint8_t init_done = 0;
  
  /* Init LCD */
  if (init_done == 2){
    result = true;
  }
  else{
    if (lcd.init() == true){
      init_done = 1;
    }
    if (init_done == 1)
    {
      /* Enable backligth */
      lcd.backlight();
    
      /* Clear display */
      lcd.clear();
    
      /* Create custom chars */
      lcd.createChar(0,Level2);
      lcd.createChar(1,Level3);
      lcd.createChar(2,Level4);
      lcd.createChar(3,Level5);
      lcd.createChar(4,Level6);
      lcd.createChar(5,Level7);
      lcd.createChar(6,carF);
      lcd.createChar(7,carR);
      result = true;
      init_done = 2;
    }
  }
  return (result);
}

void DisplayInfo::Message(uint8_t type)
{
  if (current_state != type){
     state_entry = 0;
  }
  current_state = type;
  accel_level_prev = 0;
}

void DisplayInfo::Update(void)
{
  uint16_t accel_level;
  unsigned char current_brake = BRAKE_OFF;
  unsigned char current_gear = FORWARD_G;
  unsigned char current_key = KEY_OFF;
  unsigned int  current_accel = 0;

  current_accel = accelSensor.GetValueFiltered();
  accel_level   = map(current_accel, 0, MAX_REQUEST_100XCENT, 0, 13);
  current_gear  = digitalRead(GEAR_IN);
  current_brake = digitalRead(BRAKE_IN);
  current_key   = digitalRead(KEY_IN);

  switch (current_state)
  {
    case DisplayInfo::DISPLAY_INIT:
      if(state_entry == 0) {
        state_entry = 1;
        lcd.clear();
        lcd.setCursor(6, 0); 
        lcd.write(byte(6));
        lcd.write(byte(7));
        lcd.print("______");
        lcd.setCursor(10, 1);
        lcd.print("KART Marc & Marti");
      }
      time_stored = 0;
      accel_level_prev = 0;
      lcd.scrollDisplayLeft();

    break;
    
    case DisplayInfo::SENSOR_INIT:
      if(state_entry == 0) {
        state_entry = 1;
        lcd.clear();
        lcd.setCursor(10, 1); 
        lcd.print("Checking sensors...");
      }
      lcd.scrollDisplayLeft();
    break;

    case DisplayInfo::SENSOR_ACC_ERROR:
      if(state_entry == 0) {
        state_entry = 1;
        lcd.clear();
        lcd.setCursor(0, 0); 
        lcd.print("Accel Failure :(");
        lcd.setCursor(2, 1); 
        lcd.print("Review!!");
      }
    break;

    case DisplayInfo::SENSOR_BRAKE_ERROR:
      if(state_entry == 0) {
        state_entry = 1;
        lcd.clear();
        lcd.setCursor(0, 0); 
        lcd.print("Brake Failure :(");
        lcd.setCursor(2, 1); 
        lcd.print("Review!!");
      }
    break;

    case DisplayInfo::DISPLAY_KEY_OFF:
      if(state_entry == 0) {
        state_entry = 1;
        lcd.clear();
        lcd.setCursor(0, 0); 
        lcd.print("Key is OFF.");
        lcd.setCursor(2, 1); 
        lcd.print("Turn ON to run!");
      }
    break;

    case DisplayInfo::DISPLAY_KEY_ON_ERROR:
      if(state_entry == 0) {
        state_entry = 1;
        lcd.clear(); 
        lcd.setCursor(0, 0); 
        lcd.print("Key was ON...");
        lcd.setCursor(0, 1); 
        lcd.print("Turn Key OFF/ON");
      }
    break;
    
    case DisplayInfo::DISPLAY_RUNNING:
      if(state_entry == 0) {
        state_entry = 1;
        lcd.clear(); 
        setTime(0);
        time_stored = now();
        split_tasks = 0;
      }
      /* Task split in 4 actions, to be less time consume */
      switch (split_tasks)
      {
        case 0:
          split_tasks++;
          // store last time before to stop
          if ((accel_level == 0) && (accel_level_prev > 0)){
            time_stored = now();
          }
          // frozen time
          else if (accel_level == 0){
            setTime(time_stored);
          }
          accel_level_prev = accel_level;
          /* First line */
          lcd.setCursor(5, 0);
        break;

        case 1:
          split_tasks++;
          printDigits(hour());
          lcd.write(':');
          printDigits(minute());
          lcd.write(':');
          printDigits(second());
        break;
        
        case 2:
          split_tasks++;
          /* Second line */
          lcd.setCursor(0, 1);
          if (current_gear == FORWARD_G){
            lcd.write('D');
          }
          else{
            lcd.write('R');
          }
          lcd.print(" <");
        break;
        case 3:
          split_tasks++;
          if (current_brake == BRAKE_OFF)
          {
            for (uint8_t iloop = 0; iloop < accel_level; iloop++)
            {
              lcd.write(byte(iloop/2));
            }
            for (uint8_t iloop2 = (accel_level+3); iloop2 < 15; iloop2++)
            {
              lcd.write(' ');
            }
          }
          else{
            lcd.print("--BRAKING---");
          }
          lcd.write('>');
        break;

        default:
          split_tasks = 0;
        break;
    }
    break;

    default:
      current_state = DisplayInfo::DISPLAY_INIT;
    break;
  }

}


void printDigits(int digits) {
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}
