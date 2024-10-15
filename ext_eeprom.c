#include <xc.h>
#include "main.h"
#include "i2c.h"
#include "ext_eeprom.h"



void write_ext_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE_EEPROM); // unique id
	i2c_write(address); //writing the address
	i2c_write(data); //data 
	i2c_stop();
    for(int i=3000;i--;);
}

unsigned char read_ext_eeprom(unsigned char address)
{
	unsigned char data;
	i2c_start(); 
	i2c_write(SLAVE_WRITE_EEPROM); //unique ID
	i2c_write(address); 
	i2c_rep_start();
	i2c_write(SLAVE_READ_EEPROM); 
	data = i2c_read();
	i2c_stop();

	return data;
}