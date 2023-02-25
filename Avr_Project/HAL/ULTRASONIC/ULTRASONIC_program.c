#include"../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMERS/TIMERS_interface.h"

#include "ULTRASONIC_config.h"
#include "ULTRASONIC_interface.h"
#include "ULTRASONIC_private.h"
#include<util/delay.h>

void ICU_HW(void);
void Timer1ovf(void);

u8 Global_u8Flag=0;
u32 Global_u32Timer1ovfVal=0;

void UltraSonic_voidInit(void)
{
	DIO_voidSetPinDirection( ULTRA_SONIC_TRIG_PORT, ULTRA_SONIC_TRIG_PIN,OUTPUT);
	DIO_voidSetPinDirection( ULTRA_SONIC_ECHO_PORT, ULTRA_SONIC_ECHO_PIN,INPUT);
	DIO_voidSetPinValue( ULTRA_SONIC_ECHO_PORT, ULTRA_SONIC_ECHO_PIN, NO_PULLUP);

	ICU_voidSetSenseControl(RISING_EDGE);
	ICU_voidInterruptControl(ENABLE);
	
	ICU_voidSetCallBackFunction(&ICU_HW);
	TIMERS_voidTimer1OVFSetCallBackFunction(&Timer1ovf);
}

u64 UltraSonic_u64GetDistanic(void)
{
	DIO_voidSetPinValue(PORTA,PIN0,HIGH);
	_delay_us(10);
	DIO_voidSetPinValue(PORTA,PIN0,LOW);

	TIMERS_voidTimer1SetPreloadValue(0);
	Global_u8Flag=0;

	while(Global_u8Flag==0);
	TIMERS_voidTimer1SetPreloadValue(0);
	ICU_voidSetSenseControl(FALLING_EDGE);

	while(Global_u8Flag==1);

	u64 Local_u64Distance=65536*Global_u32Timer1ovfVal+ICU_u16ReadInputCapture();
	Local_u64Distance/=58;
	ICU_voidSetSenseControl(RISING_EDGE);

	return Local_u64Distance;
}

void ICU_HW(void)
{
	Global_u8Flag++;
	if(Global_u8Flag==1)
	{
		Global_u32Timer1ovfVal=0;
	}
}

void Timer1ovf(void)
{
	Global_u32Timer1ovfVal++;
}





