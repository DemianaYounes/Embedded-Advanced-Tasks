#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "EEPROM_Interface.h"
#include "EEPROM_Private.h"
#include "EEPROM_Cfg.h"

static void (*EEPROM_Fptr) (void)=NULLPTR;
/*static*/ volatile bool_t Intr_Flag = TRUE;

void EEPROM_Init(void)
{
	/*Do Nothing*/
}
void EEPROM_write(u16 Copy_u16Address, u8 Copy_u8Data)
{
	/* Wait for completion of previous write */
	while(READ_BIT(EECR,EEWE));
	/* Set up address and data registers */
	EEAR = Copy_u16Address;
	EEDR = Copy_u8Data;
	/* Write logical one to EEMWE */
	SET_BIT(EECR, EEMWE);
	/* Start EEPROM write by setting EEWE */
	SET_BIT(EECR, EEWE);
}
u8 EEPROM_read(u16 Copy_u16Address)
{
	/* Wait for completion of previous write */
	while(READ_BIT(EECR, EEWE));
	/* Set up address register */
	EEAR = Copy_u16Address;
	/* Start EEPROM read by writing EERE */
	SET_BIT(EECR, EERE);
	/* Return data from data register */
	return EEDR;
}

/**************************** EEPROM Interrupt functions **************************************/
void EEPROM_EnableInterrupt(void)
{
	SET_BIT(EECR, EERIE);
}

void EEPROM_DisableInterrupt(void)
{
	CLR_BIT(EECR, EERIE);
}

u8 EEPROM_WriteDataInterrupt(u16 Copy_u16Address, u8 Copy_u8Data)
{
	if (Intr_Flag==TRUE)
	{
		/* Set up address and data registers */
		EEAR = Copy_u16Address;
		EEDR = Copy_u8Data;
		/* Write logical one to EEMWE */
		SET_BIT(EECR, EEMWE);
		/* Start EEPROM write by setting EEWE */
		SET_BIT(EECR, EEWE);
		
		Intr_Flag = FALSE;
	}
	return Intr_Flag;
}

/**************************** EEPROM Call Back functions **************************************/
void EEPROM_SetCallBack(void(*LocalFptr)(void))
{
	EEPROM_Fptr = LocalFptr;
}

/**************************** EEPROM ISR functions **************************************/

ISR(EE_RDY_vect)
{
	Intr_Flag = TRUE;

	if (EEPROM_Fptr != NULLPTR)
	{
		EEPROM_Fptr();
	}
}