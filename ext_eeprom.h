#ifndef EXT_EEPROM
#define EXT_EEPROM

#define SLAVE_READ_EEPROM		0xA1 //Slave address last bit is read 
#define SLAVE_WRITE_EEPROM		0xA0


void write_ext_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_ext_eeprom(unsigned char address1);

#endif