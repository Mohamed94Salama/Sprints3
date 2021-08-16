#ifndef DIO_H_
#define DIO_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MANIPULATE.h"

typedef enum {PORTA, PORTB, PORTC, PORTD} enuDIOPortNo_t;
typedef enum {PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7,
				  PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7,
				  PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7,
				  PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7} enuDIOPinNo_t;
typedef enum {INPUT, OUTPUT} enuDIOPinDirection_t;
typedef enum {NO_CONNECTION, PULL_UP_ENABLE} enuDIOPinPullupResistorEnable_t;

/*************************************************************************************************
* Parameters	: enuDIOPinNo, enuDIOPinDirection, enuDIOPinPullupResistorEnable
* Return Value	: enuErrorStatus_t
* Description  : Initialize one DIO pin according to the configuration
*************************************************************************************************/
enuErrorStatus_t DIO_PinInit(enuDIOPinNo_t enuDIOPinNo, enuDIOPinDirection_t enuDIOPinDirection, enuDIOPinPullupResistorEnable_t enuDIOPinPullupResistorEnable);
/*************************************************************************************************
* Parameters	: enuDIOPortNo, u8DIOPortDirection, u8DIOPortPullupResistorEnable
* Return Value	: enuErrorStatus_t
* Description  : Initialize one DIO port according to the configuration
*************************************************************************************************/
enuErrorStatus_t DIO_PortInit(enuDIOPortNo_t enuDIOPortNo, uint8_t u8DIOPortDirection, uint8_t u8DIOPortPullupResistorEnable);
/*************************************************************************************************
* Parameters	: enuDIOPinNo, u8PinData
* Return Value	: enuErrorStatus_t
* Description  : Write a digital value into the selected DIO pin
*************************************************************************************************/
enuErrorStatus_t DIO_PinWrite(enuDIOPinNo_t enuDIOPinNo, uint8_t u8PinData);
/*************************************************************************************************
* Parameters	: enuDIOPortNo, u8PortData
* Return Value	: enuErrorStatus_t
* Description  : Write a digital value into the selected DIO port
*************************************************************************************************/
enuErrorStatus_t DIO_PortWrite(enuDIOPortNo_t enuDIOPortNo, uint8_t u8PortData);
/*************************************************************************************************
* Parameters	: enuDIOPinNo, pu8PinData
* Return Value	: enuErrorStatus_t
* Description  : Read a digital value from the selected DIO pin
*************************************************************************************************/
enuErrorStatus_t DIO_PinRead(enuDIOPinNo_t enuDIOPinNo, uint8_t* pu8PinData);
/*************************************************************************************************
* Parameters	: enuDIOPortNo, pu8PortData
* Return Value	: enuErrorStatus_t
* Description  : Read a digital value from the selected DIO port
*************************************************************************************************/
enuErrorStatus_t DIO_PortRead(enuDIOPortNo_t enuDIOPortNo, uint8_t* pu8PortData);
/*************************************************************************************************
* Parameters	: enuDIOPinNo
* Return Value	: enuErrorStatus_t
* Description  : Toggle the digital value of the selected DIO pin
*************************************************************************************************/
enuErrorStatus_t DIO_PinToggle(enuDIOPinNo_t enuDIOPinNo);
/*************************************************************************************************
* Parameters	: enuDIOPortNo
* Return Value	: enuErrorStatus_t
* Description  : Toggle the digital value of the selected DIO port
*************************************************************************************************/
enuErrorStatus_t DIO_PortToggle(enuDIOPortNo_t enuDIOPortNo);

#endif /* DIO_H_ */