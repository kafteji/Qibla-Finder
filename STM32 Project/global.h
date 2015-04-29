#ifndef GLOBAL_H
#define GLOBAL_H 

#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include <stdio.h>
#include "stm32f3_discovery_lsm303dlhc.h"
#include "stm32f3_discovery_l3gd20.h"

#define ABS(x)         (x < 0) ? (-x) : x


#define PI                         (float)     3.14159265f



#define LSM_Acc_Sensitivity_2g     (float)     1.0f            /*!< accelerometer sensitivity with 2 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_4g     (float)     0.5f            /*!< accelerometer sensitivity with 4 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_8g     (float)     0.25f           /*!< accelerometer sensitivity with 8 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_16g    (float)     0.0834f         /*!< accelerometer sensitivity with 12 g full scale [LSB/mg] */



#define MAX_SIZE 25

// for start and end fields in BT_Packet  

#define START (uint8_t) 0x65

#define END (uint8_t) 0x66

// for id field in BT_Packet 

#define COMMAND (uint8_t) 0x67

#define DATA (uint8_t) 0x68

// define the length field content

#define LENGTH (uint8_t) 0x25

// define finite state machine 

#define IDLE (uint8_t) 0x40

#define NORTH_DETECTION (uint8_t) 0x41

#define GPS_DATA (uint8_t) 0x42

#define SHOW_DIRECTION (uint8_t) 0x43



// The Bluetooth packet

struct BT_Packet
{
	uint8_t start ;
	uint8_t id;
	uint8_t length;
	uint8_t data[MAX_SIZE-4];
	uint8_t end ;
	
};
typedef struct BT_Packet BT_Packet;

//finder struct to execute the state machine 

struct finderState
{
	uint8_t currentState ;
	uint8_t nextState;
	
};
typedef struct finderState finderState ;


#endif