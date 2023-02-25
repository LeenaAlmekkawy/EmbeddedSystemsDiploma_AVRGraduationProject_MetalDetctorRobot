#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "Metal_Sensor_interface.h"
#include "Metal_Sensor_private.h"
#include "Metal_Sensor_config.h"

void MetalSensor_voidInit()
{
	DIO_voidSetPinDirection(Metal_Sensor_Port,Metal_Sensor_Pin,INPUT);
}
u8 MetalSensor_u8SensorRead()
{
    u8 Local_u8SensorRead;
    Local_u8SensorRead=DIO_u8GetPinValue(Metal_Sensor_Port,Metal_Sensor_Pin);
	return Local_u8SensorRead;
}
