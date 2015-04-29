#include "gps.h"
#include "bluetoothHandler.h"
#include "string.h"
#include "global.h"



//   an example of a targeted GPRMC Message 
//   $GPRMC,094330.000,A,3113.3156,N,12121.2686,E,0.51,193.93,171210,,,A*68<CR><LF>
//   72

void GPS_receive_data(BT_Packet* packet){

                uint8_t buffer[72]={0}, received_char;
		int  finished = 0, counter = 0, i=0; 
                
		
		while(finished == 0){

			memset(buffer, 0x00, sizeof (buffer));  
			while(received_char != '\n'){

				received_char = GPS_USART_Receive_Byte();
				buffer[counter]= received_char ;
				counter++;
			}
			counter =0;
			i=0 ;
			if((buffer[0] == '$') && (buffer[1] == 'G') && (buffer[2] == 'P') && (buffer[3] == 'R') && (buffer[4] == 'M') && (buffer[5] == 'C')){
				if(buffer[18] == 'A'){
					counter = 20 ;
					while(buffer[counter] != ','){
						packet->data[i]= buffer[counter] ;
						i++;
						counter++ ;
					}
					counter = 30 ;
					packet->data[i] = buffer[counter];
					counter = 32 ;
					i++ ;
					while(buffer[counter] != ','){
						packet->data[i]= buffer[counter] ;
						i++;
						counter++ ;
					}
					counter=43 ;
					packet->data[i]= buffer[counter] ;
					finished = 1;

				}

			}

		} 
}
