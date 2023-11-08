#ifndef EXEEPROM_INTERFACE_H_
#define EXEEPROM_INTERFACE_H_
void ExEEPROM_voidInit(void);
void ExEEPROM_voidWriteByte(u16 copy_u16EEPROM_Add,u8 copy_u8DataByte);
void ExEEPROM_voidReadByte(u16 copy_u16EEPROM_Add,u8* copy_pu8DataByte);


#endif /* EXEEPROM_INTERFACE_H_ */