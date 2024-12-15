#include "i2c_.h"

void i2c_setup(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0));
	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C7);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C7));
	I2CMasterInitExpClk(I2C7_BASE, SysCtlClockGet(), false);
}

void I2C0_sendSingleByte(uint8_t slave_addr, char data)
{
I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);
I2CMasterDataPut(I2C0_BASE, data);
I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
while(I2CMasterBusy(I2C0_BASE));
}

void I2C0_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[])
{
uint8_t i;
I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);
I2CMasterDataPut(I2C0_BASE, by[0]);
I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
while(I2CMasterBusy(I2C0_BASE));
for (i = 1; i < numOfBytes - 1; i++)
	  {
      I2CMasterDataPut(I2C0_BASE, by[i]);
      I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
      while(I2CMasterBusy(I2C0_BASE));
    }
I2CMasterDataPut(I2C0_BASE, by[numOfBytes - 1]);
I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
while(I2CMasterBusy(I2C0_BASE));
}

void I2C7_sendSingleByte(uint8_t slave_addr, char data)
{
I2CMasterSlaveAddrSet(I2C7_BASE, slave_addr, false);
I2CMasterDataPut(I2C7_BASE, data);
I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_SINGLE_SEND);
while (I2CMasterBusy(I2C7_BASE));
}

void I2C7_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[])
{
uint8_t i;
I2CMasterSlaveAddrSet(I2C7_BASE, slave_addr, false);
I2CMasterDataPut(I2C7_BASE, by[0]);
I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_BURST_SEND_START);
while(I2CMasterBusy(I2C7_BASE));
for (i = 1; i < numOfBytes - 1; i++)
	  {
			I2CMasterDataPut(I2C7_BASE, by[i]);
			I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
			while (I2CMasterBusy(I2C7_BASE));
    }
I2CMasterDataPut(I2C7_BASE, by[numOfBytes - 1]);
I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
while (I2CMasterBusy(I2C7_BASE));
}
