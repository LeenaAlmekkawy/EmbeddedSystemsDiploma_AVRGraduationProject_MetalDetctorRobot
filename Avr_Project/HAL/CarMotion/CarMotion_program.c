#include"../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include"CarMotion_interface.h"
#include"CarMotion_private.h"
#include"CarMotion_config.h"

void CarMotion_voidInit(void)
{
	DIO_voidSetPinDirection (DCM1_PORT,DCM1_IN1_PIN, OUTPUT);
	DIO_voidSetPinDirection (DCM1_PORT,DCM1_IN2_PIN, OUTPUT);
	DIO_voidSetPinDirection (DCM2_PORT,DCM2_IN3_PIN, OUTPUT);
	DIO_voidSetPinDirection (DCM2_PORT,DCM2_IN4_PIN, OUTPUT);
}

void CarMotion_voidMoveForward(void)
{
	 DIO_voidSetPinValue (DCM1_PORT,DCM1_IN1_PIN, HIGH);
	 DIO_voidSetPinValue (DCM1_PORT,DCM1_IN2_PIN, LOW);
	 DIO_voidSetPinValue (DCM2_PORT,DCM2_IN3_PIN, HIGH);
	 DIO_voidSetPinValue (DCM2_PORT,DCM2_IN4_PIN, LOW);
}

void CarMotion_voidMoveBackward(void)
{
	 DIO_voidSetPinValue (DCM1_PORT,DCM1_IN1_PIN, LOW);
	 DIO_voidSetPinValue (DCM1_PORT,DCM1_IN2_PIN, HIGH);
	 DIO_voidSetPinValue (DCM2_PORT,DCM2_IN3_PIN, LOW);
	 DIO_voidSetPinValue (DCM2_PORT,DCM2_IN4_PIN, HIGH);
}

void CarMotion_voidTurnLeft(void)
{
	 DIO_voidSetPinValue (DCM1_PORT,DCM1_IN1_PIN, LOW);
	 DIO_voidSetPinValue (DCM1_PORT,DCM1_IN2_PIN, LOW);
	 DIO_voidSetPinValue (DCM2_PORT,DCM2_IN3_PIN, HIGH);
	 DIO_voidSetPinValue (DCM2_PORT,DCM2_IN4_PIN, LOW);

}


void CarMotion_voidTurnRight(void)
{
	DIO_voidSetPinValue (DCM1_PORT,DCM1_IN1_PIN, HIGH);
	DIO_voidSetPinValue (DCM1_PORT,DCM1_IN2_PIN, LOW);
	DIO_voidSetPinValue (DCM2_PORT,DCM2_IN3_PIN, LOW);
	DIO_voidSetPinValue (DCM2_PORT,DCM2_IN4_PIN, LOW);
}

void CarMotion_voidStop(void)
{
	DIO_voidSetPinValue (DCM1_PORT,DCM1_IN1_PIN, LOW);
	DIO_voidSetPinValue (DCM1_PORT,DCM1_IN2_PIN, LOW);
	DIO_voidSetPinValue (DCM2_PORT,DCM2_IN3_PIN, LOW);
	DIO_voidSetPinValue (DCM2_PORT,DCM2_IN4_PIN, LOW);
}
