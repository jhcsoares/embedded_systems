#ifndef __I2C__H__
#define __I2C__H__

#define PART_TM4C1294NCPDT 1

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

void i2c_setup(void);
void I2C0_sendSingleByte(uint8_t slave_addr, char data);
void I2C0_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[]);
void I2C7_sendSingleByte(uint8_t slave_addr, char data);
void I2C7_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[]);

#endif // __I2C__H__
