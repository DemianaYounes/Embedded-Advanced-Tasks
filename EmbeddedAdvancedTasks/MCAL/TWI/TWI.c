#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

#include "TWI_Interface.h"
#include "TWI_Private.h"
#include "TWI_Cfg.h"

void TWI_voidMasterInit(u8 Copu_u8SlaveAddress)
{
	/*Set clock frequency to 400kbps*/
	/*1-Set TWBR to 2*/
	TWBR=2;
	/*2-Clear the 2 bits of TWPS*/
	CLR_BIT(TWCR,TWPS0);
	CLR_BIT(TWCR,TWPS1);
	TWAR = 0b00000010;
	/*Initialize the node address*/
	if(Copu_u8SlaveAddress!=0)
	{
		TWDR=Copu_u8SlaveAddress<<1;
	}
	/*Enable TWI*/
	SET_BIT(TWCR,TWEN);
}
void TWI_voidSlaveInit(u8 Copu_u8SlaveAddress)
{
	/*Initialize the node address*/
	TWDR=Copu_u8SlaveAddress<<1;
	/*Enable TWI*/
	SET_BIT(TWCR,TWEN);
}
TWI_ErrStatus TWI_SendStartCondition(void)
{
	TWI_ErrStatus Local_ErrStatus=NoError;
	/*Send start condition on the bus*/
	SET_BIT(TWCR,TWSTA);
	
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWINT);
	/*Wait until the interrupt flag is raised again and the previous operation is completed*/
	while(READ_BIT(TWCR,TWINT)==0);
	/*Check the operation status in the status register*/
	if((TWSR &0XF8)!=TWI_START)
	{
		Local_ErrStatus=StartCondionErr;
	}
	else
	{
		/*Do nothing*/
	}
	
	return Local_ErrStatus;
}
TWI_ErrStatus TWI_SendRepeatedStart(void)
{
	TWI_ErrStatus Local_ErrStatus=NoError;
	/*Send start condition on the bus*/
	SET_BIT(TWCR,TWSTA);
	
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWINT);
	
	/*Wait until the interrupt flag is raised again and the previous operation is completed*/
	while(READ_BIT(TWCR,TWINT)==0);
	/*Check the operation status in the status register*/
	if((TWSR &0XF8)!=TWI_REP_START)
	{
		Local_ErrStatus=RepeatedStartErr;
	}
	else
	{
		/*Do nothing*/
	}
	
	return Local_ErrStatus;
}
TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_ErrStatus=NoError;
	/*Clear the start condition bit*/
	CLR_BIT(TWCR,TWSTA);
	
	/*Set the slave address in the 7 MSB in the data register*/
	TWDR=Copy_u8SlaveAddress<<1;
	CLR_BIT(TWDR,0);  /*For write request*/
	
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWINT);
	
	/*Wait until the interrupt flag is raised again and the previous operation is completed*/
	while(READ_BIT(TWCR,TWINT)==0);
	/*Check the operation status in the status register*/
	if((TWSR &0XF8)!=TWI_MT_SLA_W_ACK)
	{
		Local_ErrStatus=SlaveAddressWithWriteErr;
	}
	else
	{
		/*Do nothing*/
	}
		
	return Local_ErrStatus;
}
TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_ErrStatus=NoError;
	/*Clear the start condition bit*/
	CLR_BIT(TWCR,TWSTA);
	
	/*Set the slave address in the 7 MSB in the data register*/
	TWDR=Copy_u8SlaveAddress<<1;
	SET_BIT(TWDR,0);  /*For Read request*/
	
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWINT);
	
	/*Wait until the interrupt flag is raised again and the previous operation is completed*/
	while(READ_BIT(TWCR,TWINT)==0);
	/*Check the operation status in the status register*/
	if((TWSR &0XF8)!=TWI_MT_SLA_R_ACK)
	{
		Local_ErrStatus=SlaveAddressWithReadErr;
	}
	else
	{
		/*Do nothing*/
	}
	return Local_ErrStatus;
}
TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrStatus Local_ErrStatus=NoError;
	/*Write the data byte */
	TWDR=Copy_u8DataByte;
	
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWINT);
	
	/*Wait until the interrupt flag is raised again and the previous operation is completed*/
	while(READ_BIT(TWCR,TWINT)==0);
	/*Check the operation status in the status register*/
	if((TWSR &0XF8)!=TWI_MT_DATA_ACK)
	{
		Local_ErrStatus=MasterWriteByteErr;
	}
	else
	{
		/*Do nothing*/
	}
	
	return Local_ErrStatus;
}
TWI_ErrStatus TWI_MasterReadDataByte(u8*Copy_u8DataByte)
{
	TWI_ErrStatus Local_ErrStatus=NoError;
	/*Enable master generation acknowledge bit after receiving the data*/
	SET_BIT(TWCR,TWEA);
	
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWINT);
	
	/*Wait until the interrupt flag is raised again and the previous operation is completed*/
	while(READ_BIT(TWCR,TWINT)==0);
	/*Check the operation status in the status register*/
	if((TWSR &0XF8)!=TWI_MR_DATA_ACK)
	{
	Local_ErrStatus=MasterReadByteErr;
	}
	else
	{
		/*Read the received data*/
		*Copy_u8DataByte=TWDR;
	}
	
	return Local_ErrStatus;
}
void TWI_SendStopCondition(void)
{
	/*Generate stop condition on the bus*/
	SET_BIT(TWCR,TWSTO);
	
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWINT);
}
