/****************************************************************
*****************************************************************
** Project :- Detector Robot With Alarm(based on AVR Atmega 32)**
** Names   :- Leena Elmekkawy -- Samuel Maged                  **
** Version :-  (1)                                             **
*****************************************************************
****************************************************************/

/*********** LIB **********/
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
/*********** MCAL *********/
#include"../MCAL/DIO/DIO_interface.h"
#include"../MCAL/TIMERS/TIMERS_interface.h"
#include"../MCAL/GIE/GIE_interface.h"
/*********** HAL **********/
#include"../HAL/ULTRASONIC/ULTRASONIC_interface.h"
#include"../HAL/SERVO/SERVO_interface.h"
#include"../HAL/CarMotion/CarMotion_interface.h"
#include"../HAL/Metal_Sensor/Metal_Sensor_interface.h"
/****** Speed Coniguration and Max Distance ********/
#define SPEED_CTC_VALUE__LOW_SPEED                155
#define SPEED_CTC_VALUE__HIGH_SPEED               220
#define SERVO_REFERENCE_DISTANCE                  30
#define METAL_FOUND                               0
void APP_voidRobotInit(void);

void main(void)
{
	/* Calling Function called "APP_voidRobotInit" that has all Inializations Functions of the Project */
	APP_voidRobotInit();
	/* Set Mode 14 to make the servo move and adjust its position to look forward but disable normal mode at first */
	TIMERS_voidTimer1DisableNormalMode();
	TIMERS_voidTimer1SetMode14();
	/* Then Let the servo look forward */
	HSERVO_voidInit();
	HSERVO_voidLookForward();
    /* Delay 2s */ 
	TIMERS_voidSetBusyWaitTimer0_ms(2000);
	/* Disable Mode 14 */
	TIMERS_voidTimer1DisableMode14();
	/* Enable global interrupt */
    GIE_voidEnableGlobalInterrupt();

	while(1)
	{
		/* Init the car moves with low speed */
		TIMERS_voidTimer2SetCompareMatchValue(SPEED_CTC_VALUE__LOW_SPEED);
		/* Let the car moves forward */
		CarMotion_voidMoveForward();
        /* Read The Sensor if there was a metal or not !! */
		u8 Local_u8SensorRead = MetalSensor_u8SensorRead();
		if(Local_u8SensorRead==METAL_FOUND )
		{
			/*** Stop Car ***/
			CarMotion_voidStop();
			/* Turn on Buzzer */
			DIO_voidSetPinValue(PORTA,PIN2,HIGH);
            /* Delay 5s */
			TIMERS_voidSetBusyWaitTimer0_ms(5000);
			/* Turn off Buzzer then continue its motion */
			DIO_voidSetPinValue(PORTA,PIN2,LOW);
		}
        /* Inialize ULTRASONIC */
		UltraSonic_voidInit();
		u64 Local_u64Distance;
		/*Measure the distance in front of the robot to the closest barrier */
		Local_u64Distance=UltraSonic_u64GetDistanic();
		//If distance coming from ultrasonic is less than reference distance then enter the following if condition
		if(Local_u64Distance<SERVO_REFERENCE_DISTANCE)
		{
		   /*In this condition the robot will make the following
		      1- Make the servo move right and left
		      2- Measure the distance at each side
		      3- compare the distance and then move right or left
		   */
			CarMotion_voidStop();
			
			TIMERS_voidTimer1DisableNormalMode();
			TIMERS_voidTimer1SetMode14();
			
			HSERVO_voidInit();
			HSERVO_voidTurnRight();
			TIMERS_voidSetBusyWaitTimer0_ms(2000);
			
			TIMERS_voidTimer1DisableMode14();
			UltraSonic_voidInit();
			u64 Local_u64DistanceRight;
			Local_u64DistanceRight=UltraSonic_u64GetDistanic();

			TIMERS_voidTimer1DisableNormalMode();
			TIMERS_voidTimer1SetMode14();
			
			HSERVO_voidInit();
			HSERVO_voidTurnLeft();
			TIMERS_voidSetBusyWaitTimer0_ms(2000);

			TIMERS_voidTimer1DisableMode14();
			UltraSonic_voidInit();
			u64 Local_u64DistanceLeft;
			Local_u64DistanceLeft=UltraSonic_u64GetDistanic();

			TIMERS_voidTimer1DisableNormalMode();
			TIMERS_voidTimer1SetMode14();
			
			HSERVO_voidInit();
			HSERVO_voidLookForward();
			TIMERS_voidSetBusyWaitTimer0_ms(2000);

			if(Local_u64DistanceLeft>=Local_u64DistanceRight&&Local_u64DistanceLeft>SERVO_REFERENCE_DISTANCE )
			{  
		    CarMotion_voidMoveBackward();
			TIMERS_voidSetBusyWaitTimer0_ms(200);
			TIMERS_voidTimer2SetCompareMatchValue(SPEED_CTC_VALUE__HIGH_SPEED );
			
			CarMotion_voidTurnRight();
			TIMERS_voidSetBusyWaitTimer0_ms(1100);
			}
			else if(Local_u64DistanceRight>=Local_u64DistanceLeft&&Local_u64DistanceRight>SERVO_REFERENCE_DISTANCE )
			{ 
		    CarMotion_voidMoveBackward();
			TIMERS_voidSetBusyWaitTimer0_ms(200);
			TIMERS_voidTimer2SetCompareMatchValue(SPEED_CTC_VALUE__HIGH_SPEED );

			CarMotion_voidTurnLeft();
			TIMERS_voidSetBusyWaitTimer0_ms(700);
			}
			else
			{   	    CarMotion_voidMoveBackward();
		      	TIMERS_voidSetBusyWaitTimer0_ms(200);
				TIMERS_voidTimer2SetCompareMatchValue(254 );
				CarMotion_voidTurnLeft();
				TIMERS_voidSetBusyWaitTimer0_ms(1000);


			}
			TIMERS_voidTimer1DisableMode14();
		}
	}
}
void APP_voidRobotInit(void)
{
	/**** OC2 to generate FastPWM **************/
	DIO_voidSetPinDirection(PORTD,PIN7,OUTPUT);
	/***** Buzzer Pin ******/
	DIO_voidSetPinDirection(PORTA,PIN2,OUTPUT); 
    /*******************************************/
	CarMotion_voidInit();
	MetalSensor_voidInit();
	TIMERS_voidTimer0Init();
	TIMERS_voidTimer1Init();
	TIMERS_voidTimer2Init();
	/**Controlling the speed of car **/ 
	TIMERS_voidTimer2SetCompareMatchValue(SPEED_CTC_VALUE__LOW_SPEED);
}
