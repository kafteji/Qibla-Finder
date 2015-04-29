#ifndef DIRECTION_H
#define DIRECTION_H 


#include "global.h"
#include "bluetoothHandler.h"


void sendLocation(const BT_Packet* packet);
uint8_t getDirection(void);


#endif