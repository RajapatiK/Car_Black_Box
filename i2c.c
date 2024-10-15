#include <xc.h>
#include "i2c.h"


void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON1 = 0x28;

	SSPADD = 0x31;
	/* Use I2C levels, worked also with '0' */
	CKE = 0;
	/* Disable slew rate control  worked also with '0' */
	SMP = 1;
	/* Clear SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear bus collision flag */
	BCLIF = 0;
}

void i2c_idle(void)
{
	while (!SSPIF);
    //0 : instruction is not completed
    //1 : instruction is completed
	SSPIF = 0;
}

void i2c_ack(void)
{
	if (ACKSTAT)
	{
		/* Do debug print here if required */
	}
}

void i2c_start(void)
{
	SEN = 1;
	i2c_idle();
    //is to start the communication to start the communication we have to set it as 1
    //setting it as one is to check whether the instruction is completed or not completed
}

void i2c_stop(void)
{
	PEN = 1;
	i2c_idle();
    // pen 1 is is to initiate the stop condition ;
}

void i2c_rep_start(void)
{
	RSEN = 1;
	i2c_idle();
    //if i set the bit as 1 to repeat the start again to write the bits again;
}

void i2c_write(unsigned char data)
{
	SSPBUF = data;
	i2c_idle();
    //its a half duplex so only one byte of data at a time and the idle is to check whether the instruction is completed or not
}

void i2c_rx_mode(void)
{
	RCEN = 1;
	i2c_idle();
    //in order to set the receive mode on master and idle to check the instruction is completed or not
}

void i2c_no_ack(void)
{
	ACKDT = 1;
	ACKEN = 1;
    //we have to send the  bit as 1 because we are not sending any acknowledge we have to inform.
    //so that we are making the enable bit as 1 for acknowledge so that we can send the data acknowledge
}

unsigned char i2c_read(void)
{
	i2c_rx_mode();
	i2c_no_ack();
    //is to receive a data from the slave and we gave to enable bit to send no acknowledge 

	return SSPBUF;//where the data is stored
}