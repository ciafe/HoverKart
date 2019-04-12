//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Automatic generated C-code by the application:
//     FSM Editor v1.4r3
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Methodology: Hierarchical Switch-case state. [v1.5r1]
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Exported function: void KartControl(void);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Initialization proposed by the user (Start).
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
  #include "Config.h"
  
  /* h_fsm types */
  #ifndef _FSM_TYPES_H_
  #define _FSM_TYPES_H_
      typedef unsigned char   T_bit;
      typedef unsigned char   T_u8;
      typedef char            T_char;
      typedef unsigned short  T_u16;
  #endif  /* _FSM_TYPES_H_ */
  
  
  void MotorsForward(unsigned int accel_req, float factor);
  void MotorsReverse(unsigned int accel_req, float factor);
  void MotorsDisable(void);
  void MotorsEnable(void);
  
  
  #define BASE_DELAY         50u
  #define DELAY_8S           8000u / BASE_DELAY 
  #define DELAY_6S           6000u / BASE_DELAY 
  #define DELAY_5S           5000u / BASE_DELAY 
  #define DELAY_3S           3000u / BASE_DELAY 
  #define DELAY_2S           2000u / BASE_DELAY 
  #define DELAY_1S           1000u / BASE_DELAY 
  #define DELAY_AFTER_BRAKE  DELAY_1S
  
  
  #define MOTOR_MIN_POWER      10u
  #define MOTOR_MIN_ACCEL      20u

  
  /* Conditions */
  #define BRAKE_PRESSED()        (current_brake == BRAKE_ON)
  #if defined(DEBUG_DISABLE_HW_INPUTS_CHECK)
  #define SENSOR_ACCEL_OK()      (true)
  #define SENSOR_BRAKE_OK()      (true)
  #else
  #define SENSOR_ACCEL_OK()      (accelSensor.InRange() == true)
  #define SENSOR_BRAKE_OK()      (current_brake == BRAKE_OFF)
  #endif
  #define KEY_ON()               (current_key == KEY_ON)
  #define KEY_OFF()              (current_key == KEY_OFF)
  #if defined(DEBUG_COMMANDS_STATES)
  #define DEBUG_PRINT(x)         Serial.println(x)
  #else
  #define DEBUG_PRINT(x)         {}
  #endif
  
  
  unsigned char keycheck = false;
  unsigned int  delaycount = 0;
  unsigned int  powerMotor = 0;
  unsigned int  current_accel = 0;
  unsigned char current_brake = BRAKE_OFF;
  unsigned char current_gear = FORWARD_G;
  unsigned char current_key = KEY_OFF;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Initialization proposed by the user (End).
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Entry flags (Start).
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  static T_bit entryFsmFlg = 0U;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Entry flags (End).
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Automatic initialization (Start).
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 // States index.
  #define  i_SENSOR_CHECK   ((T_u8)0)
  #define  i_KEY_CHECK      ((T_u8)1)
  #define  i_RUN_STOPPED    ((T_u8)2)
  #define  i_RUN_FORWARD    ((T_u8)3)
  #define  i_RUN_REVERSE    ((T_u8)4)
  #define  i_RUN_BRAKING_F  ((T_u8)5)
  #define  i_BRAKE_DELAY_F  ((T_u8)6)
  #define  i_RUN_BRAKING_R  ((T_u8)7)
  #define  i_BRAKE_DELAY_R  ((T_u8)8)

 // Index variable.
T_u8 ind_KartControl = i_SENSOR_CHECK;

// Macros & functions.
// Force the FSM to the initial state.
#define KartControl_Init() { ind_KartControl = i_SENSOR_CHECK; entryFsmFlg = 0U; }

// This is not a history FSM.
#define _KartControl_Init()  {KartControl_Init(); /* Children: */ }

// Confirm that the FSM has reached the state:[RUN_STOPPED].
#define KartControl_IsIn_RUN_STOPPED() (ind_KartControl == i_RUN_STOPPED)

// Confirm that the FSM has reached the state:[RUN_FORWARD].
#define KartControl_IsIn_RUN_FORWARD() (ind_KartControl == i_RUN_FORWARD)

// Confirm that the FSM has reached the state:[RUN_REVERSE].
#define KartControl_IsIn_RUN_REVERSE() (ind_KartControl == i_RUN_REVERSE)

// Confirm that the FSM has reached the state:[RUN_BRAKING_F].
#define KartControl_IsIn_RUN_BRAKING_F() (ind_KartControl == i_RUN_BRAKING_F)

// Confirm that the FSM has reached the state:[BRAKE_DELAY_F].
#define KartControl_IsIn_BRAKE_DELAY_F() (ind_KartControl == i_BRAKE_DELAY_F)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Automatic initialization (End).
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Local child functions  (Start).
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Local child functions  (End).
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM dispatcher function to be called by the O.S.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void KartControl(void)
{
    // User actions to be executed before analyse the state.
    /* Read real pedal sensor value */
    current_accel = accelSensor.GetValueFiltered();
        
    /* Read gear sensor value */
    current_gear  = digitalRead(GEAR_IN);
        
    /* Read brake sensor value */
    current_brake = digitalRead(BRAKE_IN);
    
    /* Read key sensor value */
    current_key = digitalRead(KEY_IN);

    // Next state analyser.
    switch(ind_KartControl){
        case i_SENSOR_CHECK:
            // Entry check
            if(!((T_bit)entryFsmFlg)){
                entryFsmFlg = (T_bit)1;
                // Entry actions
                MotorsDisable();
                kartLcd.Message(DisplayInfo::DISPLAY_INIT);
                delaycount = 0;
                DEBUG_PRINT("SENSOR_CHECK");
            }
            // Next state selection.
            if(SENSOR_ACCEL_OK() &&
               SENSOR_BRAKE_OK() &&
               (delaycount > DELAY_8S)){
                // Pointing to the next state.
               #if defined(DEBUG_DISABLE_HW_INPUTS_CHECK)
                ind_KartControl = i_RUN_STOPPED;
               #else
                ind_KartControl = i_KEY_CHECK;
               #endif
                // Reset entry flag
                entryFsmFlg = 0U;
            }
            else if (delaycount > DELAY_8S){
              if (!SENSOR_ACCEL_OK())
              {
                kartLcd.Message(DisplayInfo::SENSOR_ACC_ERROR);
              }
              else
              {
                kartLcd.Message(DisplayInfo::SENSOR_BRAKE_ERROR);
              }
            }
        break;
        case i_KEY_CHECK:
            // Entry check
            if(!((T_bit)entryFsmFlg)){
                entryFsmFlg = (T_bit)1;
                // Entry actions
                keycheck = false;
                MotorsDisable();
                DEBUG_PRINT("KEY_CHECK");
            }
            // Next state selection.
            if(KEY_OFF()){	// [1].
                // Transition actions (Meally).
                keycheck = true;
                kartLcd.Message(DisplayInfo::DISPLAY_KEY_OFF);
            }else if(KEY_ON() && (keycheck == false)){	// [2].
                // Transition actions (Meally).
                kartLcd.Message(DisplayInfo::DISPLAY_KEY_ON_ERROR);
            }else if(KEY_ON()){	// [3].
                // Pointing to the next state.
                ind_KartControl = i_RUN_STOPPED;
                // Reset entry flag
                entryFsmFlg = 0U;
            }
        break;
        case i_RUN_STOPPED:
            // Entry check
            if(!((T_bit)entryFsmFlg)){
                entryFsmFlg = (T_bit)1;
                // Entry actions
                kartLcd.Message(DisplayInfo::DISPLAY_RUNNING);
                MotorsEnable();
                DEBUG_PRINT("RUN STOPPED");
            }
            // State actions (Moore).
            if (current_gear == FORWARD_G){
                MotorsForward(0, FACTOR_RUN);
            }
            else{
                MotorsReverse(0, FACTOR_RUN);
            }

            // Next state selection.
            if(BRAKE_PRESSED()){	// [1].
            }else if((current_gear == FORWARD_G)
                     &&
                     (current_accel > MOTOR_MIN_ACCEL)){	// [2].
                // Pointing to the next state.
                ind_KartControl = i_RUN_FORWARD;
                // Reset entry flag
                entryFsmFlg = 0U;
            }else if((current_gear == REVERSE_G)
                     &&
                     (current_accel > MOTOR_MIN_ACCEL)){	// [3].
                // Pointing to the next state.
                ind_KartControl = i_RUN_REVERSE;
                // Reset entry flag
                entryFsmFlg = 0U;
            }else if(KEY_OFF()){	// [4].
                // Pointing to the next state.
                ind_KartControl = i_KEY_CHECK;
                // Reset entry flag
                entryFsmFlg = 0U;
            }
        break;
        case i_RUN_FORWARD:
            // Entry check
            if(!((T_bit)entryFsmFlg)){
                entryFsmFlg = (T_bit)1;
                // Entry actions
                DEBUG_PRINT("RUN FOR");
            }
            // State actions (Moore).
            MotorsForward(current_accel, FACTOR_RUN);
            // Next state selection.
            if((current_gear == REVERSE_G)
               ||
               BRAKE_PRESSED()
               ||
               KEY_OFF()){	// [1].
                // Pointing to the next state.
                ind_KartControl = i_RUN_BRAKING_F;
                // Reset entry flag
                entryFsmFlg = 0U;
            }else if((current_accel < MOTOR_MIN_ACCEL)
                     &&
                     (powerMotor < MOTOR_MIN_POWER)){	// [2].
                // Pointing to the next state.
                ind_KartControl = i_RUN_STOPPED;
                // Reset entry flag
                entryFsmFlg = 0U;
            }
        break;
        case i_RUN_REVERSE:
            // Entry check
            if(!((T_bit)entryFsmFlg)){
                entryFsmFlg = (T_bit)1;
                // Entry actions
                DEBUG_PRINT("RUN REV");
            }
            // State actions (Moore).
            MotorsReverse(current_accel, FACTOR_RUN);
            // Next state selection.
            if((current_gear == FORWARD_G)
               ||
               BRAKE_PRESSED()
               ||
               KEY_OFF()){	// [1].
                // Pointing to the next state.
                ind_KartControl = i_RUN_BRAKING_R;
                // Reset entry flag
                entryFsmFlg = 0U;
            }else if((current_accel < MOTOR_MIN_ACCEL)
                     &&
                     (powerMotor < MOTOR_MIN_POWER)){	// [2].
                // Pointing to the next state.
                ind_KartControl = i_RUN_STOPPED;
                // Reset entry flag
                entryFsmFlg = 0U;
            }
        break;
        case i_RUN_BRAKING_F:
            // Entry check
            if(!((T_bit)entryFsmFlg)){
                entryFsmFlg = (T_bit)1;
                // Entry actions
                delaycount = 0;
                DEBUG_PRINT("BRAKE FOR");
            }
            // State actions (Moore).
            MotorsForward(0, FACTOR_BRAKE);
            // Next state selection.
            if((powerMotor < MOTOR_MIN_POWER)){	// [1].
                // Pointing to the next state.
                ind_KartControl = i_BRAKE_DELAY_F;
                // Reset entry flag
                entryFsmFlg = 0U;
            }else if(KEY_OFF()
                     ||
                     BRAKE_PRESSED()){	// [2].
                // Transition actions (Meally).
                delaycount = 0;
            }else if((current_gear == FORWARD_G)){	// [3].
                // Pointing to the next state.
                ind_KartControl = i_RUN_FORWARD;
                // Reset entry flag
                entryFsmFlg = 0U;
            }
        break;
        case i_BRAKE_DELAY_F:
            // Entry check
            if(!((T_bit)entryFsmFlg)){
                entryFsmFlg = (T_bit)1;
                // Entry actions
                delaycount = 0;
            }
            // State actions (Moore).
            MotorsForward(0, FACTOR_BRAKE);
            // Next state selection.
            if((delaycount > DELAY_AFTER_BRAKE)
               &&
               KEY_OFF()){	// [1].
                // Pointing to the next state.
                ind_KartControl = i_KEY_CHECK;
                // Reset entry flag
                entryFsmFlg = 0U;
            }else if((delaycount > DELAY_AFTER_BRAKE)){	// [2].
                // Pointing to the next state.
                ind_KartControl = i_RUN_STOPPED;
                // Reset entry flag
                entryFsmFlg = 0U;
            }
        break;
        case i_RUN_BRAKING_R:
            // Entry check
            if(!((T_bit)entryFsmFlg)){
                entryFsmFlg = (T_bit)1;
                // Entry actions
                delaycount = 0;
                DEBUG_PRINT("BRAKE REV");
            }
            // State actions (Moore).
            MotorsReverse(0, FACTOR_BRAKE);
            // Next state selection.
            if((powerMotor < MOTOR_MIN_POWER)){	// [1].
                // Pointing to the next state.
                ind_KartControl = i_BRAKE_DELAY_R;
                // Reset entry flag
                entryFsmFlg = 0U;
            }else if(KEY_OFF()
                     ||
                     BRAKE_PRESSED()){	// [2].
                // Transition actions (Meally).
                delaycount = 0;
            }else if((current_gear == REVERSE_G)){	// [3].
                // Pointing to the next state.
                ind_KartControl = i_RUN_REVERSE;
                // Reset entry flag
                entryFsmFlg = 0U;
            }
        break;
        case i_BRAKE_DELAY_R:
            // Entry check
            if(!((T_bit)entryFsmFlg)){
                entryFsmFlg = (T_bit)1;
                // Entry actions
                delaycount = 0;
            }
            // State actions (Moore).
            MotorsReverse(0, FACTOR_BRAKE);
            // Next state selection.
            if((delaycount > DELAY_AFTER_BRAKE)
               &&
               KEY_OFF()){	// [1].
                // Pointing to the next state.
                ind_KartControl = i_KEY_CHECK;
                // Reset entry flag
                entryFsmFlg = 0U;
            }else if((delaycount > DELAY_AFTER_BRAKE)){	// [2].
                // Pointing to the next state.
                ind_KartControl = i_RUN_STOPPED;
                // Reset entry flag
                entryFsmFlg = 0U;
            }
        break;
    }

    // User actions to be executed after analyse the state.
    if (delaycount < 0xFFFF)
    {
        delaycount++;
    }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Ending code proposed by the user (Start).
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void MotorsForward(unsigned int accel_req, float factor)
{
    unsigned int powerRequest = 0;
    
    powerRequest = map(accel_req, 0, 1000, 0, LIMIT_POWER_FORWARD);
    
    powerMotor = (powerRequest * factor) + (powerMotor * (1 - factor));
    
    motorL.SetPower(powerMotor, HoverMotor::FORWARD);
    motorR.SetPower(powerMotor, HoverMotor::FORWARD);
    
    #if defined(DEBUG_PRINT_POWER)
    Serial.println(powerMotor);
    #endif
}

void MotorsReverse(unsigned int accel_req, float factor)
{
    unsigned int powerRequest = 0;
    
    powerRequest = map(accel_req, 0, 1000, 0, LIMIT_POWER_REVERSE);
    
    powerMotor = (powerRequest * factor) + (powerMotor * (1 - factor));
    
    motorL.SetPower(powerMotor, HoverMotor::REVERSE);
    motorR.SetPower(powerMotor, HoverMotor::REVERSE);

    #if defined(DEBUG_PRINT_POWER)
    Serial.print("-");
    Serial.println(powerMotor);
    #endif
}

void MotorsDisable(void)
{
    motorR.Disable();
    motorL.Disable();
    DEBUG_PRINT("DIS");
}

void MotorsEnable(void)
{
    motorR.Enable();
    motorL.Enable();
    DEBUG_PRINT("EN");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Ending code proposed by the user (End).
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  End of the automatic generated C-code.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
