#include "direction.h"

void sendLocation(const BT_Packet* packet){

	uint8_t buffer[MAX_SIZE];
	int i;

	buffer[0]=packet->start;
	buffer[1]=packet->id;
	buffer[2]=packet->length;
	for ( i = 0; i < MAX_SIZE-4; ++i)
	{
		buffer[i+3]=packet->data[i];
	}
	buffer[MAX_SIZE-1]=packet->end;
	Bluetooth_USART_Send_Buffer(buffer, MAX_SIZE);
}



uint8_t getDirection(){
	uint8_t direction;
	uint8_t receivedData[MAX_SIZE];

	Bluetooth_USART_Receive_Buffer(receivedData,MAX_SIZE);
	if ((receivedData[0] == START) && (receivedData[1]== COMMAND) && (receivedData[2] == LENGTH) && (receivedData[24] == END ))
	{
		direction = receivedData[3];
	} else{
		direction = 0x99;
	}
	return direction;
}