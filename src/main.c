/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f411e_discovery.h"
#include "stm32f411e_discovery_audio.h"

#include "audio.h"

uint8_t flag = 1;
uint8_t flag_play = 0;

int main(void)
{

	HAL_Init();
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);


	if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, 100, AUDIO_FREQUENCY_16K)!= AUDIO_OK)
		while(1);
	if(BSP_AUDIO_IN_Init(I2S_AUDIOFREQ_16K, 16, 1)!= AUDIO_OK)
		while(1);


	while(1){



		if(flag){

			BSP_LED_On(LED4);
			BSP_AUDIO_IN_Record(dataMic, 30000);

			flag = 0;
		}

		if(flag_play){
			BSP_AUDIO_IN_PDMToPCM(dataMic, dataOut);
			BSP_LED_On(LED5);
			BSP_AUDIO_OUT_Play(dataOut, 30000);
			flag_play = 0;
		}

	}
}

void BSP_AUDIO_OUT_TransferComplete_CallBack(void){
	BSP_LED_Off(LED5);
	flag = 0;
}

void BSP_AUDIO_IN_TransferComplete_CallBack(void){
	BSP_AUDIO_IN_Pause();
	BSP_LED_Off(LED4);
	flag_play = 1;
}
