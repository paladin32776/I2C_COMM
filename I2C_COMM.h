#include "Arduino.h"
#include <Wire.h>

#ifndef I2C_COMM_H
#define I2C_COMM_H

#define I2C_COMM_DELAY_US 20

class I2C_COMM
{
  protected:
      unsigned char addr;
      unsigned char read_byte(unsigned char regbyte);
      unsigned int read_word(unsigned char regbyte);
      unsigned int read_word_no_reg();
      void read_multi_bytes(unsigned char regbyte, unsigned char N, unsigned char* byte_array);
      void write_regbyte(unsigned char regbyte);
      void write_byte(unsigned char regbyte, unsigned char databyte);
      void write_word(unsigned char regbyte, unsigned int dataword);
      void write_multi_bytes(unsigned char regbyte, unsigned char N, unsigned char* byte_array);
  public:
      I2C_COMM(unsigned char _addr);
      I2C_COMM(unsigned char _addr, unsigned char SDApin, unsigned char SCLpin);
};

#endif // I2C_COMM_H
