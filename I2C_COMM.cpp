#include "I2C_COMM.h"
#define PRINTBIN(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? '1' : '0'); // Prints a binary number with leading zeros (Automatic Handling)

I2C_COMM::I2C_COMM(unsigned char _addr)
{
  Wire.begin(14,2);
  Wire.setClockStretchLimit(200000);// was default 230 uS, now 200ms
  addr = _addr;
  delay(I2C_COMM_DELAY_US);
}

I2C_COMM::I2C_COMM(unsigned char _addr, unsigned char SDApin, unsigned char SCLpin)
{
  Wire.begin(SDApin,SCLpin);
  Wire.setClockStretchLimit(200000);// was default 230 uS, now 200ms
  addr = _addr;
  delay(I2C_COMM_DELAY_US);
}

unsigned char I2C_COMM::read_byte(unsigned char regbyte)
{
  Wire.beginTransmission(addr);
  Wire.write(byte(regbyte));
  Wire.endTransmission(false);
  delayMicroseconds(I2C_COMM_DELAY_US);
  Wire.requestFrom(addr, (byte)1);
  unsigned char databyte = Wire.read();
  return databyte;
}

unsigned int I2C_COMM::read_word(unsigned char regbyte)
{
  Wire.beginTransmission(addr);
  Wire.write(byte(regbyte));
  Wire.endTransmission(false);
  delayMicroseconds(I2C_COMM_DELAY_US);
  Wire.requestFrom(addr, (byte)2);
  unsigned int dataword = 0;
  while (Wire.available())
    dataword = (dataword<<8)+Wire.read();
  return dataword;
}

void I2C_COMM::write_regbyte(unsigned char regbyte)
{
  Wire.beginTransmission(addr);         // transmit to device #addr
  Wire.write(byte(regbyte));            // sends instruction byte
  Wire.endTransmission();               // stop transmitting
  delayMicroseconds(I2C_COMM_DELAY_US);
}

void I2C_COMM::write_byte(unsigned char regbyte, unsigned char databyte)
{
  Wire.beginTransmission(addr);         // transmit to device #addr
  Wire.write(byte(regbyte));            // sends instruction byte
  Wire.write(byte(databyte));           // sends value byte
  Wire.endTransmission();               // stop transmitting
  delayMicroseconds(I2C_COMM_DELAY_US);
}

void I2C_COMM::write_word(unsigned char regbyte, unsigned int dataword)
{
  Wire.beginTransmission(addr);         // transmit to device #addr
  Wire.write(byte(regbyte));            // sends instruction byte
  Wire.write(byte(dataword>>8));        // sends upper byte
  Wire.write(byte(dataword & 0xFF));    // sends lower byte
  Wire.endTransmission();               // stop transmitting
  delayMicroseconds(I2C_COMM_DELAY_US);
}
