#ifndef CONFIG_H
#define CONFIG_H

/***** General Definition *****************************/
typedef enum
{
  FORWARD_G  = true,
  REVERSE_G  = false
} GearSensorType;

typedef enum
{
  BRAKE_ON   = true,
  BRAKE_OFF  = false
} BrakeSensoType;

typedef enum
{
  KEY_ON   = false,
  KEY_OFF  = true
} KeySensoType;

#define MAX_REQUEST_100XCENT  1000

/******* Arduino HW configuration *********************/
#define KEY_IN           2u
#define BRAKE_IN         3u
#define GEAR_IN          4u
#define UART_RX_R        8u
#define UART_TX_R        9u
#define UART_RX_L       10u
#define UART_TX_L       11u

#define HOVER_SENSOR_V2    // or HOVER_SENSOR_V1

#if defined(HOVER_SENSOR_V2)
#define BAUD_RATE_HOVER_SENSOR      52600UL
#else
#define BAUD_RATE_HOVER_SENSOR      26300UL
#endif
#define HOVER_SENSOR_SIM_MAX_VALUE   2000

/******* Functional configuration limits **************/
#define LIMIT_POWER_FORWARD  500u    //50%
#define LIMIT_POWER_REVERSE  200u    //14%
#define FACTOR_BRAKE         0.14
#define FACTOR_RUN           0.08

/* Comment or uncomment to enable command line commands snd debug info printf */
//#define DEBUG_COMMANDS_STATES
//#define DEBUG_PRINT_POWER
//#define DEBUG_DISABLE_HW_INPUTS_CHECK

#endif
