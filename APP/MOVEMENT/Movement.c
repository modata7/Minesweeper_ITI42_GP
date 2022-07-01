/*
 * Motion.c
 *
 *  Created on: Jun 23, 2022
 *      Author: 20106
 */

#include "Std_types.h"
#include "stdio.h"
#include "GPIO.h"
#include "RCC.h"
#include "NVIC.h"
#include "Uart_cfg.h"
#include "Uart.h"
#include "Systick.h"

/*Static Functions Prototypes*/
static void Motion_Init(void);
static void Motion_vidForWard();
static void Motion_vidBackWard();
static void Motion_vidLeft();
static void Motion_vidRight();
static void UartInit(Uart_Cnfg * Uart);
static void Motion_vidClearServoPin(void);

/*Pin out Definitions*/
#define FRONT_RIGHT												GPIO_u8PIN_04
#define FRONT_LEFT												GPIO_u8PIN_06
#define BACK_RIGHT												GPIO_u8PIN_00
#define BACK_LEFT												GPIO_u8PIN_02

#define MOTOR_1													GPIO_u8PIN_05
#define MOTOR_2													GPIO_u8PIN_07
#define MOTOR_3													GPIO_u8PIN_01
#define MOTOR_4													GPIO_u8PIN_10

#define SERVO_PIN												GPIO_u8PIN_01

void main(void)
{
	/*Local Variables*/
	u8 Loc_Char;
	Uart_Cnfg Loc_Uart;

/*	Enable Prephirals*/
	RCC_enuEnablePrephiralClock(RCC_AHB_GPIOA);
	RCC_enuEnablePrephiralClock(RCC_AHB_GPIOB);
	RCC_enuEnablePrephiralClock(RCC_APB2_USART1);

	/*Uart Init*/
	UartInit(&Loc_Uart);
	Uart_vidInit(USART1,&Loc_Uart);

	/*GPIO Pins Init*/
	GPIO_enuSetPinMode(PORTA,GPIO_u8PIN_09,OUTPUT_HIGH_SPEED_AF_PP);
	GPIO_enuSetPinMode(PORTA,GPIO_u8PIN_10,OUTPUT_HIGH_SPEED_AF_PP);

	GPIO_enuSetPinMode(PORTA,SERVO_PIN,OUTPUT_HIGH_SPEED_PP);

	GPIO_enuSetPinAlternateFunction(PORTA,GPIO_u8PIN_09,AF07_USART1_2);
	GPIO_enuSetPinAlternateFunction(PORTA,GPIO_u8PIN_10,AF07_USART1_2);

	/*Motion Init*/
	Motion_Init();

	/*Systick Init*/
	Systick_init ();
	Systick_SetTickTime_ms(1);
	Systick_RegisterCBF(Motion_vidClearServoPin);

	while(1)
	{
		/*Receive command from the Bluetooth Module HC - 05*/
		Uart_enuReceiveSynchronus(&Loc_Char,1,USART1);

		/*Check the Received Character*/
		switch (Loc_Char)
		{
		case 'F':
			Motion_vidForWard();			//Call Motion_vidForWard
			break;

		case 'B':
			Motion_vidBackWard();			// Call Motion_vidBackWard
			break;

		case 'L':
			Motion_vidLeft();				//Call Motion_vidLeft
			break;

		case 'R':
			Motion_vidRight();				//Call Motion_vidRight
			break;

		case 'W':
			GPIO_enuSetPinValue(PORTB,SERVO_PIN,GPIO_HIGH); //Set Servo Pin

			Systick_Start();								//Start a 1ms Delay
			break;

		default:
			break;
		}

		/*Software Delay*/
		for (int Loc_Iterator = 0;Loc_Iterator < 200000;Loc_Iterator++)
		{
			asm("NOP");
		}

		/*Clear GPIO Pins*/
		GPIO_enuSetPinValue(PORTA,MOTOR_1,GPIO_LOW);
		GPIO_enuSetPinValue(PORTA,MOTOR_2,GPIO_LOW);
		GPIO_enuSetPinValue(PORTB,MOTOR_3,GPIO_LOW);
		GPIO_enuSetPinValue(PORTB,MOTOR_4,GPIO_LOW);

		GPIO_enuSetPinValue(PORTA,FRONT_RIGHT,GPIO_LOW);
		GPIO_enuSetPinValue(PORTA,FRONT_LEFT,GPIO_LOW);
		GPIO_enuSetPinValue(PORTB,BACK_RIGHT,GPIO_LOW);
		GPIO_enuSetPinValue(PORTB,BACK_LEFT,GPIO_LOW);
	}
}

/*Motion Init*/
void Motion_Init(void)
{
	GPIO_enuSetPinMode(PORTA,FRONT_RIGHT,OUTPUT_HIGH_SPEED_PP);
	GPIO_enuSetPinMode(PORTA,MOTOR_1,OUTPUT_HIGH_SPEED_PP);

	GPIO_enuSetPinMode(PORTA,FRONT_LEFT,OUTPUT_HIGH_SPEED_PP);
	GPIO_enuSetPinMode(PORTA,MOTOR_2,OUTPUT_HIGH_SPEED_PP);

	GPIO_enuSetPinMode(PORTB,BACK_RIGHT,OUTPUT_HIGH_SPEED_PP);
	GPIO_enuSetPinMode(PORTB,MOTOR_3,OUTPUT_HIGH_SPEED_PP);

	GPIO_enuSetPinMode(PORTB,BACK_LEFT,OUTPUT_HIGH_SPEED_PP);
	GPIO_enuSetPinMode(PORTB,MOTOR_4,OUTPUT_HIGH_SPEED_PP);

	GPIO_enuSetPinValue(PORTB,SERVO_PIN,GPIO_LOW);

}

/*Forward Motion*/
void Motion_vidForWard()
{
	GPIO_enuSetPinValue(PORTA,FRONT_RIGHT,GPIO_HIGH);
	GPIO_enuSetPinValue(PORTA,MOTOR_1,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTA,FRONT_LEFT,GPIO_HIGH);
	GPIO_enuSetPinValue(PORTA,MOTOR_2,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTB,BACK_RIGHT,GPIO_LOW);
	GPIO_enuSetPinValue(PORTB,MOTOR_3,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTB,BACK_LEFT,GPIO_LOW);
	GPIO_enuSetPinValue(PORTB,MOTOR_4,GPIO_HIGH);
}

/*Backward Motion*/
void Motion_vidBackWard()
{
	GPIO_enuSetPinValue(PORTA,FRONT_LEFT,GPIO_HIGH);
	GPIO_enuSetPinValue(PORTA,MOTOR_1,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTB,BACK_RIGHT,GPIO_HIGH);
	GPIO_enuSetPinValue(PORTB,MOTOR_3,GPIO_HIGH);
}

/*Left Motion*/
void Motion_vidLeft()
{
	GPIO_enuSetPinValue(PORTA,FRONT_RIGHT,GPIO_HIGH);
	GPIO_enuSetPinValue(PORTA,MOTOR_1,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTA,FRONT_LEFT,GPIO_HIGH);
	GPIO_enuSetPinValue(PORTA,MOTOR_2,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTB,BACK_RIGHT,GPIO_HIGH);
	GPIO_enuSetPinValue(PORTB,MOTOR_3,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTB,BACK_LEFT,GPIO_HIGH);
	GPIO_enuSetPinValue(PORTB,MOTOR_4,GPIO_HIGH);
}

/*Right Motion*/
void Motion_vidRight()
{
	GPIO_enuSetPinValue(PORTA,FRONT_RIGHT,GPIO_LOW);
	GPIO_enuSetPinValue(PORTA,MOTOR_1,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTA,FRONT_LEFT,GPIO_LOW);
	GPIO_enuSetPinValue(PORTA,MOTOR_2,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTB,BACK_RIGHT,GPIO_LOW);
	GPIO_enuSetPinValue(PORTB,MOTOR_3,GPIO_HIGH);

	GPIO_enuSetPinValue(PORTB,BACK_LEFT,GPIO_LOW);
	GPIO_enuSetPinValue(PORTB,MOTOR_4,GPIO_HIGH);
}

/*Uart Init*/
static void UartInit(Uart_Cnfg * Uart)
{
	Uart->BaudRate = UART_9600BR;
	Uart->DataSize = UART_DATA_8BIT;
	Uart->RE = UART_TE_EN;
	Uart->TE = UART_RE_EN;
	Uart->StopBits = UART_STOP_BIT_ONE;
}

/*Systick Clear Servo Pin Call Back Function*/
static void Motion_vidClearServoPin(void)
{
	Systick_Disable();								//Disable systick
	GPIO_enuSetPinValue(PORTB,SERVO_PIN,GPIO_LOW);	//Clear Servo Pin
}
