#include "main.h"




void Bluetooth_GPS_USART_Init(){

       GPIO_InitTypeDef  Bluetooth_GPIO_InitStruct; 
       USART_InitTypeDef Bluetooth_USART_InitStruct; 
       GPIO_InitTypeDef  GPS_GPIO_InitStruct; 
       USART_InitTypeDef GPS_USART_InitStruct; 

  
       // Initializing GPIOD and USART2 for the Bluetooth module 

       RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
       Bluetooth_GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6; // -- PD5 = USART2_TX -- PD6 = USART2_RX 
       Bluetooth_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;                                
       Bluetooth_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
       Bluetooth_GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
       Bluetooth_GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
       GPIO_Init(GPIOD, &Bluetooth_GPIO_InitStruct);   

       
       GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_7);
       GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_7);
       
       RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

       USART_DeInit(USART2);
       Bluetooth_USART_InitStruct.USART_BaudRate = 9600;
       Bluetooth_USART_InitStruct.USART_WordLength = USART_WordLength_8b;
       Bluetooth_USART_InitStruct.USART_StopBits = USART_StopBits_1;
       Bluetooth_USART_InitStruct.USART_Parity = USART_Parity_No;
       Bluetooth_USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
       Bluetooth_USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
       USART_Init(USART2,&Bluetooth_USART_InitStruct);
      
       USART_Cmd(USART2, ENABLE);

       // initializing GPIOC and USART3 for the GPS module 

       RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
       GPS_GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6; // -- PC10 = USART3_TX -- PC11 = USART3_RX 
       GPS_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;                                
       GPS_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
       GPS_GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
       GPS_GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
       GPIO_Init(GPIOC, &GPS_GPIO_InitStruct);


       GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_7);
       GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_7);
       
       RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);


       USART_DeInit(USART3);
       GPS_USART_InitStruct.USART_BaudRate = 9600;
       GPS_USART_InitStruct.USART_WordLength = USART_WordLength_8b;
       GPS_USART_InitStruct.USART_StopBits = USART_StopBits_1;
       GPS_USART_InitStruct.USART_Parity = USART_Parity_No;
       GPS_USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
       GPS_USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
       USART_Init(USART3,&GPS_USART_InitStruct);
      
       USART_Cmd(USART3, ENABLE);


  
}



uint8_t Bluetooth_USART_Receive_Byte(void) 
{
  //wait until the RXNE bit is set
  while (((USART2->ISR & USART_FLAG_RXNE) == RESET) ) {}
  return((uint8_t) USART_ReceiveData(USART2));
}



void Bluetooth_USART_Receive_Buffer(uint8_t* Read_buffer, uint32_t size)
{
  int i = 0;
  for (i=0; i<size; i++)
  {
    Read_buffer[i] = Bluetooth_USART_Receive_Byte();
  }   
} 


void Bluetooth_USART_Send_Byte(uint8_t byte)
{
  //wait until TXE bit is set
  while ((USART2->ISR & USART_FLAG_TXE) == RESET) {}
  USART_SendData(USART2, byte); 
} 


void Bluetooth_USART_Send_Buffer(uint8_t* buffer, uint32_t size)
{
  int i = 0;
  for (i=0; i<size; i++)
  {
    Bluetooth_USART_Send_Byte((buffer[i]));
  }
}


uint8_t GPS_USART_Receive_Byte(void) 
{
  //wait until the RXNE bit is set
  while (((USART3->ISR & USART_FLAG_RXNE) == RESET) ) {}
  return((uint8_t) USART_ReceiveData(USART3));
}



void GPS_USART_Receive_Buffer(uint8_t* Read_buffer, uint32_t size)
{
  int i = 0;
  for (i=0; i<size; i++)
  {
    Read_buffer[i] = GPS_USART_Receive_Byte();
  }   
} 

