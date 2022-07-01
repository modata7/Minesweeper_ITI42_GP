

#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "Servo.h"
#include "HMagnet.h"
#include "Uart.h"
#include "Sched.h"
#include "NVIC.h"
#include "Collection.h"
#include "Detection.h"



int main(void)
{
	Uart_Cnfg Uart_strCfg =
	{
			. DataSize = UART_DATA_8BIT ,
			. StopBits = UART_STOP_BIT_ONE ,
			. TE = UART_TE_DIS ,
			. RE = UART_RE_EN
	};

	RCC_enuEnablePrephiralClock(RCC_AHB_GPIOA);
	RCC_enuEnablePrephiralClock(RCC_APB1_TIMER2);
	RCC_enuEnablePrephiralClock(RCC_APB2_TIMER1);

	GPIO_enuSetPinMode(PORTB,GPIO_u8PIN_05,OUTPUT_HIGH_SPEED_PP);    // gpio for magnet

	GPIO_enuSetPinMode(PORTB,GPIO_u8PIN_01,INPUT_PULL_DOWN);  // gpio for controlling the servo


	initPins();

	HMagnet_enuMagnetInit();
	Servo_vidInit(0);
	Servo_vidInit(1);

	Sched_init();
	Sched_Start();


	return 0;
}
