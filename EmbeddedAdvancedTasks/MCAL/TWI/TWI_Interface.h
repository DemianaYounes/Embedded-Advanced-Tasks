

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum{
	NoError,
	StartCondionErr,
	RepeatedStartErr,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr,
	}TWI_ErrStatus;
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_voidMasterInit(u8 Copu_u8SlaveAddress);
void TWI_voidSlaveInit(u8 Copu_u8SlaveAddress);
TWI_ErrStatus TWI_SendStartCondition(void);
TWI_ErrStatus TWI_SendRepeatedStart(void);
TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte);
TWI_ErrStatus TWI_MasterReadDataByte(u8*Copy_u8DataByte);
void TWI_SendStopCondition(void);

#endif /* TWI_INTERFACE_H_ */