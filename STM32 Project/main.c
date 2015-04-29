
#include "main.h"


BT_Packet packet ;
finderState finder;

  RCC_ClocksTypeDef RCC_Clocks;
__IO uint32_t TimingDelay = 0;
__IO uint32_t UserButtonPressed = 0;
__IO float HeadingValue = 0.0f;  
float MagBuffer[3] = {0.0f}, AccBuffer[3] = {0.0f}, Buffer[3] = {0.0f};
uint8_t Xval, Yval = 0x00;
uint8_t ledNum ;

__IO uint8_t DataReady = 0;
__IO uint8_t PrevXferComplete = 1;
uint8_t test = 't';
float fNormAcc,fSinRoll,fCosRoll,fSinPitch,fCosPitch = 0.0f, RollAng = 0.0f, PitchAng = 0.0f;
float fTiltedX,fTiltedY = 0.0f;




int main(void)
{  
  uint8_t i = 0;
  
  

  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
  

  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  STM_EVAL_LEDInit(LED7);
  STM_EVAL_LEDInit(LED8);
  STM_EVAL_LEDInit(LED9);
  STM_EVAL_LEDInit(LED10);
  
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI); 

 
  UserButtonPressed = 0x00; 
  Bluetooth_GPS_USART_Init();
  finder.currentState = IDLE ;
  finder.nextState = NORTH_DETECTION ;
  
   

  while (1)
  {   
  
    STM_EVAL_LEDOff(LED3);
    STM_EVAL_LEDOff(LED6);
    STM_EVAL_LEDOff(LED7);
    STM_EVAL_LEDOff(LED4);
    STM_EVAL_LEDOff(LED10);
    STM_EVAL_LEDOff(LED8);
    STM_EVAL_LEDOff(LED9);
    STM_EVAL_LEDOff(LED5);

    switch(finder.currentState){

    	case IDLE : 

			    	while (UserButtonPressed == 0x00)
			    {
			      /* Toggle LD3 */
			      STM_EVAL_LEDToggle(LED3);
			      /* Insert 50 ms delay */
			      Delay(5);
			      /* Toggle LD5 */
			      STM_EVAL_LEDToggle(LED5);
			      /* Insert 50 ms delay */
			      Delay(5);
			      /* Toggle LD7 */
			      STM_EVAL_LEDToggle(LED7);
			      /* Insert 50 ms delay */
			      Delay(5);
			      /* Toggle LD9 */
			      STM_EVAL_LEDToggle(LED9);
			      /* Insert 50 ms delay */
			      Delay(5);
			      /* Toggle LD10 */
			      STM_EVAL_LEDToggle(LED10);
			      /* Insert 50 ms delay */
			      Delay(5);
			      /* Toggle LD8 */
			      STM_EVAL_LEDToggle(LED8);
			      /* Insert 50 ms delay */
			      Delay(5); 
			      /* Toggle LD6 */
			      STM_EVAL_LEDToggle(LED6);
			      /* Insert 50 ms delay */
			      Delay(5);
			      /* Toggle LD4 */
			      STM_EVAL_LEDToggle(LED4);
			      /* Insert 50 ms delay */
			      Delay(5);
			    }
			     DataReady = 0x00;
			     finder.currentState=finder.nextState;
			     finder.nextState=GPS_DATA;
    			 

				 STM_EVAL_LEDOff(LED4);
				 STM_EVAL_LEDOff(LED3);
				 STM_EVAL_LEDOff(LED6);
				 STM_EVAL_LEDOff(LED7);
				 STM_EVAL_LEDOff(LED10);
				 STM_EVAL_LEDOff(LED8);
				 STM_EVAL_LEDOff(LED9);
				 STM_EVAL_LEDOff(LED5);
				 break;



		case NORTH_DETECTION :

		
				    Demo_CompassConfig();

				    
				    while (UserButtonPressed == 0x01)
				    {

				      while(DataReady !=0x05)
				      {}
				      DataReady = 0x00;
				      
				      /* Read Compass data */
				      Demo_CompassReadMag(MagBuffer);
				      Demo_CompassReadAcc(AccBuffer);
				      
				      for(i=0;i<3;i++)
				        AccBuffer[i] /= 100.0f;
				      
				      fNormAcc = sqrt((AccBuffer[0]*AccBuffer[0])+(AccBuffer[1]*AccBuffer[1])+(AccBuffer[2]*AccBuffer[2]));
				      
				      fSinRoll = -AccBuffer[1]/fNormAcc;
				      fCosRoll = sqrt(1.0-(fSinRoll * fSinRoll));
				      fSinPitch = AccBuffer[0]/fNormAcc;
				      fCosPitch = sqrt(1.0-(fSinPitch * fSinPitch));
				     if ( fSinRoll >0)
				     {
				       if (fCosRoll>0)
				       {
				         RollAng = acos(fCosRoll)*180/PI;
				       }
				       else
				       {
				         RollAng = acos(fCosRoll)*180/PI + 180;
				       }
				     }
				     else
				     {
				       if (fCosRoll>0)
				       {
				         RollAng = acos(fCosRoll)*180/PI + 360;
				       }
				       else
				       {
				         RollAng = acos(fCosRoll)*180/PI + 180;
				       }
				     }
				     
				      if ( fSinPitch >0)
				     {
				       if (fCosPitch>0)
				       {
				            PitchAng = acos(fCosPitch)*180/PI;
				       }
				       else
				       {
				          PitchAng = acos(fCosPitch)*180/PI + 180;
				       }
				     }
				     else
				     {
				       if (fCosPitch>0)
				       {
				            PitchAng = acos(fCosPitch)*180/PI + 360;
				       }
				       else
				       {
				          PitchAng = acos(fCosPitch)*180/PI + 180;
				       }
				     }

				      if (RollAng >=360)
				      {
				        RollAng = RollAng - 360;
				      }
				      
				      if (PitchAng >=360)
				      {
				        PitchAng = PitchAng - 360;
				      }
				      
				      fTiltedX = MagBuffer[0]*fCosPitch+MagBuffer[2]*fSinPitch;
				      fTiltedY = MagBuffer[0]*fSinRoll*fSinPitch+MagBuffer[1]*fCosRoll-MagBuffer[1]*fSinRoll*fCosPitch;
				      
				      HeadingValue = (float) ((atan2f((float)fTiltedY,(float)fTiltedX))*180)/PI;
				 
				      if (HeadingValue < 0)
				      {
				        HeadingValue = HeadingValue + 360;    
				      }
				      
				      if ((RollAng <= 40.0f) && (PitchAng <= 40.0f))
				      {
				        if (((HeadingValue < 25.0f)&&(HeadingValue >= 0.0f))||((HeadingValue >=340.0f)&&(HeadingValue <= 360.0f)))
				        {
				          STM_EVAL_LEDOn(LED10);
				          STM_EVAL_LEDOff(LED3);
				          STM_EVAL_LEDOff(LED6);
				          STM_EVAL_LEDOff(LED7);
				          STM_EVAL_LEDOff(LED4);
				          STM_EVAL_LEDOff(LED8);
				          STM_EVAL_LEDOff(LED9);
				          STM_EVAL_LEDOff(LED5);
				        }
				        else  if ((HeadingValue <70.0f)&&(HeadingValue >= 25.0f))
				        {
				          STM_EVAL_LEDOn(LED9);
				          STM_EVAL_LEDOff(LED6);
				          STM_EVAL_LEDOff(LED10);
				          STM_EVAL_LEDOff(LED3);
				          STM_EVAL_LEDOff(LED8);
				          STM_EVAL_LEDOff(LED5);
				          STM_EVAL_LEDOff(LED4);
				          STM_EVAL_LEDOff(LED7);
				        } 
				        else  if ((HeadingValue < 115.0f)&&(HeadingValue >= 70.0f))
				        {
				          STM_EVAL_LEDOn(LED7);
				          STM_EVAL_LEDOff(LED3);
				          STM_EVAL_LEDOff(LED4);
				          STM_EVAL_LEDOff(LED9);
				          STM_EVAL_LEDOff(LED10);
				          STM_EVAL_LEDOff(LED8);
				          STM_EVAL_LEDOff(LED6);
				          STM_EVAL_LEDOff(LED5);
				        }
				        else  if ((HeadingValue <160.0f)&&(HeadingValue >= 115.0f))
				        {
				          STM_EVAL_LEDOn(LED5);
				          STM_EVAL_LEDOff(LED6);
				          STM_EVAL_LEDOff(LED10);
				          STM_EVAL_LEDOff(LED8);
				          STM_EVAL_LEDOff(LED9);
				          STM_EVAL_LEDOff(LED7);
				          STM_EVAL_LEDOff(LED4);
				          STM_EVAL_LEDOff(LED3);
				        } 
				        else  if ((HeadingValue <205.0f)&&(HeadingValue >= 160.0f))
				        {
				          STM_EVAL_LEDOn(LED3);
				          STM_EVAL_LEDOff(LED6);
				          STM_EVAL_LEDOff(LED4);
				          STM_EVAL_LEDOff(LED8);
				          STM_EVAL_LEDOff(LED9);
				          STM_EVAL_LEDOff(LED5);
				          STM_EVAL_LEDOff(LED10);
				          STM_EVAL_LEDOff(LED7);
				        } 
				        else  if ((HeadingValue <250.0f)&&(HeadingValue >= 205.0f))
				        {
				          STM_EVAL_LEDOn(LED4);
				          STM_EVAL_LEDOff(LED6);
				          STM_EVAL_LEDOff(LED10);
				          STM_EVAL_LEDOff(LED8);
				          STM_EVAL_LEDOff(LED9);
				          STM_EVAL_LEDOff(LED5);
				          STM_EVAL_LEDOff(LED3);
				          STM_EVAL_LEDOff(LED7);
				        } 
				        else  if ((HeadingValue < 295.0f)&&(HeadingValue >= 250.0f))
				        {
				          STM_EVAL_LEDOn(LED6);
				          STM_EVAL_LEDOff(LED9);
				          STM_EVAL_LEDOff(LED10);
				          STM_EVAL_LEDOff(LED8);
				          STM_EVAL_LEDOff(LED3);
				          STM_EVAL_LEDOff(LED5);
				          STM_EVAL_LEDOff(LED4);
				          STM_EVAL_LEDOff(LED7);
				        }        
				        else  if ((HeadingValue < 340.0f)&&(HeadingValue >= 295.0f))
				        {
				          STM_EVAL_LEDOn(LED8);
				          STM_EVAL_LEDOff(LED6);
				          STM_EVAL_LEDOff(LED10);
				          STM_EVAL_LEDOff(LED7);
				          STM_EVAL_LEDOff(LED9);
				          STM_EVAL_LEDOff(LED3);
				          STM_EVAL_LEDOff(LED4);
				          STM_EVAL_LEDOff(LED5);
				        }
				      }
				      else
				      {
				        /* Toggle All LEDs */
				        STM_EVAL_LEDToggle(LED7);
				        STM_EVAL_LEDToggle(LED6);
				        STM_EVAL_LEDToggle(LED10);
				        STM_EVAL_LEDToggle(LED8);
				        STM_EVAL_LEDToggle(LED9);
				        STM_EVAL_LEDToggle(LED3);
				        STM_EVAL_LEDToggle(LED4);
				        STM_EVAL_LEDToggle(LED5);
				        /* Delay 50ms */
				        Delay(5);
				      }

                    } // while (UserButtonPressed == 0x01)

                    finder.currentState = finder.nextState;
                    finder.nextState = SHOW_DIRECTION;
                    
        
                    break;


        case GPS_DATA :


        			GPS_receive_data(&packet);

        			//completing all packet fields

        			packet.start=START;
        			packet.id=DATA;
        			packet.end=END;
        			packet.length=LENGTH;


        			finder.currentState=finder.nextState;
        			finder.nextState=IDLE;
        			break;

        
        case SHOW_DIRECTION :

        		
        			sendLocation(&packet);
        			ledNum = getDirection();
        			STM_EVAL_LEDOff(LED3);
        			STM_EVAL_LEDOff(LED4);
        			STM_EVAL_LEDOff(LED5);
        			STM_EVAL_LEDOff(LED6);
        			STM_EVAL_LEDOff(LED7);
        			STM_EVAL_LEDOff(LED8);
        			STM_EVAL_LEDOff(LED9);
        			STM_EVAL_LEDOff(LED10);
                    while (UserButtonPressed == 0x02){


                    	switch(ledNum){

                    		case 0x61 :

	                    		STM_EVAL_LEDToggle(LED3);
	                    		Delay(40);
	                    		break;

                    		case 0x68 :

                    			STM_EVAL_LEDToggle(LED4);
                    			Delay(40);
                    			break;

                    		case 0x62 :

                    			STM_EVAL_LEDToggle(LED5);
                    			Delay(40);
                    			break;

                    		case 0x67 :

                    			STM_EVAL_LEDToggle(LED6);
                    			Delay(40);
                    			break;

                    		case 0x63 :

                    			STM_EVAL_LEDToggle(LED7);
                    			Delay(40);
                    			break;

                    		case 0x66 :

                    			STM_EVAL_LEDToggle(LED8);
                    			Delay(40);
                    			break;

                    		case 0x64 :

                    			STM_EVAL_LEDToggle(LED9);
                    			Delay(40);
                    			break;

                    		case 0x65 :

                    			STM_EVAL_LEDToggle(LED10);
                    			Delay(40);
                    			break;

                    		default :

                    			// if an error occured the you must restart the process

		                    			STM_EVAL_LEDToggle(LED7);
						        STM_EVAL_LEDToggle(LED6);
						        STM_EVAL_LEDToggle(LED10);
						        STM_EVAL_LEDToggle(LED8);
						        STM_EVAL_LEDToggle(LED9);
						        STM_EVAL_LEDToggle(LED3);
						        STM_EVAL_LEDToggle(LED4);
						        STM_EVAL_LEDToggle(LED5);
						        Delay(5);


                    	}
			                  
                    }
                    finder.currentState=finder.nextState;
                    finder.nextState=NORTH_DETECTION;
                    STM_EVAL_LEDOff(LED3);
    		    STM_EVAL_LEDOff(LED6);
    	 	    STM_EVAL_LEDOff(LED7);
    		    STM_EVAL_LEDOff(LED4);
    		    STM_EVAL_LEDOff(LED10);
    		    STM_EVAL_LEDOff(LED8);
    		    STM_EVAL_LEDOff(LED9);
    	 	    STM_EVAL_LEDOff(LED5);
                    break; 






    } // end switch

    
    
    
       
   
    
  
  } 
  
  
}





/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
uint32_t LSM303DLHC_TIMEOUT_UserCallback(void)
{
  return 0;
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
uint32_t L3GD20_TIMEOUT_UserCallback(void)
{
  return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
