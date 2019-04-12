#include "HoverMotor.h"
#include "InputSensor.h"
#include "DisplayInfo.h"
#include "Filters.h"
#include "Config.h"


// Global objects
HoverMotor     motorL(UART_RX_L, UART_TX_L);
HoverMotor     motorR(UART_RX_R, UART_TX_R);
InputSensor    accelSensor(A0, 180, 700, 2.0);
DisplayInfo    kartLcd;


// Configure task intervals in ms
const int FastTaskInterval = 0;
const int MidTaskInterval  = 50;
const int SlowTaskInterval = 500;

unsigned long currentMillis = 0; 
unsigned long previousFastTaskMillis = 0;
unsigned long previousMidTaskMillis = 0;
unsigned long previousSlowTaskMillis = 0;

//DEBUG
extern unsigned char ind_KartControl;
extern  unsigned int  powerMotor;

void setup() {

#if defined(DEBUG_COMMANDS_STATES) || defined(DEBUG_PRINT_POWER)
  Serial.begin(115200);
  Serial.println("Init..");
#endif

  pinMode(BRAKE_IN, INPUT);
  pinMode(KEY_IN,   INPUT);
  pinMode(GEAR_IN,  INPUT);
}

void loop() {
  /*************** Simple Scheduler  *******************************/
  currentMillis = millis();
  
  if (currentMillis - previousFastTaskMillis >= FastTaskInterval) {
       previousFastTaskMillis = currentMillis;
       FastTaskActions();
  }

  if (currentMillis - previousMidTaskMillis >= MidTaskInterval) {
       previousMidTaskMillis = currentMillis;
       MidTaskActions();
  }

  if (currentMillis - previousSlowTaskMillis >= SlowTaskInterval) {
       previousSlowTaskMillis = currentMillis;
       SlowTaskActions();
  }
}

void FastTaskActions(void)
{
  /* Process motor communication with mainboard */
  motorL.Cyclic();
  motorR.Cyclic();
}

void MidTaskActions(void)
{
  /* Process accelerator information */
  accelSensor.Cyclic();
  /* Process Kart control */
  KartControl();
}

void SlowTaskActions(void)
{ 
  /* Display update */
  uint8_t init_finished = kartLcd.Init();
  if (init_finished == true)
  {
    kartLcd.Update();
  }
  
}

