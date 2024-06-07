extern "C"
{
#include <inttypes.h>
}

#include "Arduino.h"
#include "Wire.h"
#include "SM_16UNIVIN.h"

SM_16_UNIVIN::SM_16_UNIVIN(uint8_t stack)
{
  if (stack > 7)
    stack = 7;
  _hwAdd = UI_SLAVE_OWN_ADDRESS_BASE + stack;
  _detected = false;
}

bool SM_16_UNIVIN::begin()
{
  uint8_t value = 0;
  if ( 0 == readByte(UI_I2C_MEM_REVISION_MAJOR_ADD, &value))
  {
    _detected = true;
  }
  return _detected;
}

bool SM_16_UNIVIN::isAlive()
{
  return _detected;
}

bool SM_16_UNIVIN::writeLED(uint8_t led, bool val)
{
  if (led > UI_UNIV_CH_NR || led == 0)
  {
    return false;
  }
  if (val)
  {
    if (OK == writeByte(UI_I2C_MEM_LED_SET, led))
      return true;
  }
  else
  {
    if (OK == writeByte(UI_I2C_MEM_LED_CLR, led))
      return true;
  }
  return false;
}

bool SM_16_UNIVIN::writeLED(uint16_t val)
{
  if (OK == writeWord(UI_I2C_MEM_LEDS, val))
    return true;
  return false;
}

int SM_16_UNIVIN::readAnalogMv(uint8_t channel)
{
  int ret = 0;
  uint16_t val = 0;

  if (channel < 1 || channel > UI_UNIV_CH_NR)
  {
    return -1;
  }
  ret = readWord(UI_I2C_U0_10_IN_VAL1_ADD + (channel - 1) * UI_ANALOG_VAL_SIZE, &val);
  if (ret < 0)
    return ret;
  return val;
}

int SM_16_UNIVIN::readRes1k(uint8_t channel)
{
  int ret = 0;
  uint16_t val = 0;

  if (channel < 1 || channel > UI_UNIV_CH_NR)
  {
    return -1;
  }
  ret = readWord(UI_I2C_R_1K_CH1 + (channel - 1) * UI_ANALOG_VAL_SIZE, &val);
  if (ret < 0)
    return ret;
  return val;
}

int SM_16_UNIVIN::readRes10k(uint8_t channel)
{
  int ret = 0;
  uint16_t val = 0;

  if (channel < 1 || channel > UI_UNIV_CH_NR)
  {
    return -1;
  }
  ret = readWord(UI_I2C_R_10K_CH1 + (channel - 1) * UI_ANALOG_VAL_SIZE, &val);
  if (ret < 0)
    return ret;
  return val;
}

bool SM_16_UNIVIN::readDC(uint8_t channel)
{
  uint16_t aux = 0;

  if (channel < 1 || channel > UI_UNIV_CH_NR)
  {
    return ERROR;
  }
  if (readWord(UI_I2C_MEM_DRY_CONTACT, &aux) == OK)
  {
    if (aux & (1 << (channel - 1)))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return ERROR;
}


int SM_16_UNIVIN::readDC()
{
  uint16_t aux = 0;

  if (readWord(UI_I2C_MEM_DRY_CONTACT, &aux) == OK)
  {
    return aux;
  }
  return -1;
}


bool SM_16_UNIVIN::cfgCounter(uint8_t channel, bool enable)
{
  uint16_t aux;

  if (channel < 1 || channel > UI_UNIV_CH_NR)
  {
    return false;
  }

  if (readWord(UI_I2C_MEM_DC_CNT_ENABLE, &aux) != OK)
  {
    return false;
  }
 if(enable)
 {
	 aux |= 1 << (channel -1);
 }
 else
 {
	 aux &= ~(1 << (channel -1));
 }
  return (OK == writeWord(UI_I2C_MEM_DC_CNT_ENABLE, aux));
}

int SM_16_UNIVIN::readCounter(uint8_t channel)
{
  uint32_t val = 0;

  if (channel < 1 || channel > UI_UNIV_CH_NR)
  {
    return ERROR;
  }
  if (readDWord(UI_I2C_MEM_DC_CNT_ADD + (channel - 1) * UI_COUNTER_SIZE, &val) != OK)
  {
    return ERROR;
  }
  return val;
}

bool SM_16_UNIVIN::resetCounter(uint8_t channel)
{
  if (channel < 1 || channel > UI_UNIV_CH_NR)
  {
    return false;
  }
  return (OK == writeByte(UI_I2C_MEM_DC_CNT_RST_ADD, channel));
}


/***************** UI_I2C access functions *********************************
 *  *********************************************************************
*/
int SM_16_UNIVIN::writeByte(uint8_t add, uint8_t value)
{
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  Wire.write(value);
  return Wire.endTransmission();
}

int SM_16_UNIVIN::writeWord(uint8_t add, uint16_t value)
{
  uint8_t buff[2];

  memcpy(buff, &value, 2);
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  Wire.write(buff[0]);
  Wire.write(buff[1]);
  return Wire.endTransmission();

}
int SM_16_UNIVIN::writeDWord(uint8_t add, uint32_t value)
{
  uint8_t buff[4];
  int i = 0;

  memcpy(buff, &value, 4);
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  for (i = 0; i < 4; i++)
  {
    Wire.write(buff[i]);
  }
  return Wire.endTransmission();

}
int SM_16_UNIVIN::readByte(uint8_t add, uint8_t* value)
{
  if (0 == value)
  {
    return -1;
  }
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  if (Wire.endTransmission() != 0)
  {
    return -1;
  }
  Wire.requestFrom(_hwAdd, (uint8_t)1);
  if (1 <= Wire.available())
  {
    *value = Wire.read();
  }
  else
  {
    return -1;
  }
  return 0;
}
int SM_16_UNIVIN::readWord(uint8_t add, uint16_t* value)
{
  uint8_t buff[2];

  if (0 == value)
  {
    return -1;
  }
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  if (Wire.endTransmission() != 0)
  {
    return -1;
  }
  Wire.requestFrom(_hwAdd, (uint8_t)2);
  if (2 <= Wire.available())
  {
    buff[0] = Wire.read();
    buff[1] = Wire.read();
  }
  else
  {
    return -1;
  }
  memcpy(value, buff, 2);
  return 0;
}

int SM_16_UNIVIN::readDWord(uint8_t add, uint32_t* value)
{
  uint8_t buff[4];
  int i = 0;

  if (0 == value)
  {
    return -1;
  }
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  if (Wire.endTransmission() != 0)
  {
    return -1;
  }
  Wire.requestFrom(_hwAdd, (uint8_t)4);
  if (4 <= Wire.available())
  {
    for (i = 0; i < 4; i++)
    {
      buff[i] = Wire.read();
    }
  }
  else
  {
    return -1;
  }
  memcpy(value, buff, 4);
  return 0;
}

int SM_16_UNIVIN::readSignedDWord(uint8_t add, int32_t* value)
{
  uint8_t buff[4];
  int i = 0;

  if (0 == value)
  {
    return -1;
  }
  Wire.begin();
  Wire.beginTransmission(_hwAdd);
  Wire.write(add);
  if (Wire.endTransmission() != 0)
  {
    return -1;
  }
  Wire.requestFrom(_hwAdd, (uint8_t)4);
  if (4 <= Wire.available())
  {
    for (i = 0; i < 4; i++)
    {
      buff[i] = Wire.read();
    }
  }
  else
  {
    return -1;
  }
  memcpy(value, buff, 4);
  return 0;
}
