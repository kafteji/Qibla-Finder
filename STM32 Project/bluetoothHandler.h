#ifndef BLUETOOTHHANDLER_H
#define BLUETOOTHHANDLER_H



void Bluetooth_GPS_USART_Init(void);

uint8_t Bluetooth_USART_Receive_Byte(void);

void Bluetooth_USART_Receive_Buffer(uint8_t* Read_buffer, uint32_t size);

void Bluetooth_USART_Send_Byte(uint8_t byte);

void Bluetooth_USART_Send_Buffer(uint8_t* buffer, uint32_t size);

uint8_t GPS_USART_Receive_Byte(void);

void GPS_USART_Receive_Buffer(uint8_t* Read_buffer, uint32_t size);


#endif