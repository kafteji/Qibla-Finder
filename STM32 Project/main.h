
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/

#include "global.h"
#include "math.h"
#include "mems.h"
#include "bluetoothHandler.h"
#include "gps.h"
#include "direction.h"




// extern variables declaration 

extern BT_Packet packet ;
extern finderState finder ;


void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);



#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
