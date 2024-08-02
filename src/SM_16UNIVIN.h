/*!
 * @file SM_HomeAutomation.h
 * 
 * Designed specifically to work with the Sequent Microsysatems 
 * Sixteen Analog/Digital Inputs 8-Layer Stackable HAT for Raspberry Pi
 * 
 * ----> https://sequentmicrosystems.com/collections/all-io-cards/products/sixteen-analog-digital-inputs-8-layer-stackable-hat-for-raspberry-pi
 * 
 *   This card use I2C to communicate.
 *   
 *   Written by Alexandru Burcea for Sequent Microsystems
 * 
 *   Software License Agreement (BSD License)
 *
 *  Copyright (c) 2024, Sequent Microsystems 
 *  
 */

#ifndef SM_16UNIVIN_H_
#define SM_16UNIVIN_H_

#include "Arduino.h"
#include <inttypes.h>
#include "Wire.h"

#define ERROR -1
#define OK 0
#define UI_UNIV_CH_NR  16
#define UI_ANALOG_VAL_SIZE  2
#define UI_DIG_CH_NO 8
#define UI_COUNTER_SIZE 4
#define UI_OPTO_ENC_CH_NO 4
#define UI_CALIBRATION_KEY 0xaa
#define UI_RESET_CALIBRATION_KEY 0x55
#define UI_MODBUS_SETTINGS_SIZE_B 5

enum
{
	UI_I2C_MEM_LEDS,
	UI_I2C_MEM_LED_SET = UI_I2C_MEM_LEDS + 2,
	UI_I2C_MEM_LED_CLR,

	UI_I2C_MEM_DRY_CONTACT,

	UI_I2C_U0_10_IN_VAL1_ADD = UI_I2C_MEM_DRY_CONTACT + 2,

	UI_I2C_R_1K_CH1 = UI_I2C_U0_10_IN_VAL1_ADD + UI_UNIV_CH_NR * UI_ANALOG_VAL_SIZE,
	UI_I2C_R_10K_CH1 = UI_I2C_R_1K_CH1 + UI_UNIV_CH_NR * UI_ANALOG_VAL_SIZE,

	UI_I2C_MEM_DIAG_TEMPERATURE_ADD = UI_I2C_R_10K_CH1
		+ UI_UNIV_CH_NR * UI_ANALOG_VAL_SIZE,
	UI_I2C_MEM_DC_CNT_ENABLE,

	UI_I2C_MEM_DC_CNT_RST_ADD = UI_I2C_MEM_DC_CNT_ENABLE + 2,

	UI_I2C_MEM_DC_CNT_ADD,
	UI_I2C_MEM_DC_CNT_END_ADD = UI_I2C_MEM_DC_CNT_ADD
		+ UI_UNIV_CH_NR * UI_COUNTER_SIZE,

	UI_I2C_MEM_UPDATE_ADD = 0xaa,

	UI_I2C_MEM_CALIB_VALUE,
	UI_I2C_MEM_CALIB_CHANNEL = UI_I2C_MEM_CALIB_VALUE + 4,
	UI_I2C_MEM_CALIB_KEY, //set calib point -> 0xaa; reset calibration on the channel -> 0x55
	UI_I2C_MEM_CALIB_STATUS,

	UI_I2C_RTC_YEAR_ADD,
	UI_I2C_RTC_MONTH_ADD,
	UI_I2C_RTC_DAY_ADD,
	UI_I2C_RTC_HOUR_ADD,
	UI_I2C_RTC_MINUTE_ADD,
	UI_I2C_RTC_SECOND_ADD,
	UI_I2C_RTC_SET_YEAR_ADD,
	UI_I2C_RTC_SET_MONTH_ADD,
	UI_I2C_RTC_SET_DAY_ADD,
	UI_I2C_RTC_SET_HOUR_ADD,
	UI_I2C_RTC_SET_MINUTE_ADD,
	UI_I2C_RTC_SET_SECOND_ADD,
	UI_I2C_RTC_CMD_ADD,

	UI_I2C_MEM_WDT_RESET_ADD,
	UI_I2C_MEM_WDT_INTERVAL_SET_ADD,
	UI_I2C_MEM_WDT_INTERVAL_GET_ADD = UI_I2C_MEM_WDT_INTERVAL_SET_ADD + 2,
	UI_I2C_MEM_WDT_INIT_INTERVAL_SET_ADD = UI_I2C_MEM_WDT_INTERVAL_GET_ADD + 2,
	UI_I2C_MEM_WDT_INIT_INTERVAL_GET_ADD = UI_I2C_MEM_WDT_INIT_INTERVAL_SET_ADD
		+ 2,
	UI_I2C_MEM_WDT_RESET_COUNT_ADD = UI_I2C_MEM_WDT_INIT_INTERVAL_GET_ADD + 2,
	UI_I2C_MEM_WDT_CLEAR_RESET_COUNT_ADD = UI_I2C_MEM_WDT_RESET_COUNT_ADD + 2,
	UI_I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD,
	UI_I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD = UI_I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD
		+ 4,
	UI_I2C_MEM_BUTTON = UI_I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD + 4,
	UI_I2C_MEM_DIAG_RASP_V,
	UI_I2C_MEM_DIAG_RASP_V1,

	UI_I2C_MODBUS_SETINGS_ADD,

	UI_I2C_MEM_REVISION_HW_MAJOR_ADD = UI_I2C_MODBUS_SETINGS_ADD
		+ UI_MODBUS_SETTINGS_SIZE_B,
	UI_I2C_MEM_REVISION_HW_MINOR_ADD,
	UI_I2C_MEM_REVISION_MAJOR_ADD,
	UI_I2C_MEM_REVISION_MINOR_ADD,

	SLAVE_BUFF_SIZE = 255,
};

#define UI_SLAVE_OWN_ADDRESS_BASE 0x58

/*!
 * @brief Main Sexteen Universal inputs class
 */
class SM_16_UNIVIN
{
public:

	/*!
	 * @brief Class constructor
	 * @param stack - stack level setted from the dip-switches on the card
	 * @param wire - which I2C interface you wish to use
	 */
	SM_16_UNIVIN(uint8_t stack = 0, TwoWire *wire = &Wire);

	/*!
	 * @brief Check card presence
	 * @return Returns true is successful
	 */
	bool begin();

	/*!
	 * @brief Return card existance status
	 * @return Returns true if card is present
	 */
	bool isAlive();

	/*!
	 * @brief Turn on or Off one led
	 * @param led The led number 1..8
	 * @param val The new state true = on, false = off
	 * @return true if succeed, false else
	 */
	bool writeLED(uint8_t led, bool val);

	/*!
	 * @brief Turn on or Off all leds
	 * @param val All 16 led's state as a bitmap
	 * @return true if succeed, false else
	 */
	bool writeLED(uint16_t val);

	/*!
	 * @brief Read the value in millivolts of one analog input channel, range 0 ... 10000
	 * @param channel The analog input channel number 1..16
	 * @return Returns analog input millivolts 
	 */
	int readAnalogMv(uint8_t channel);

	/*!
	 * @brief Read the value in ohms of one 1k thermocouple input channel, range 0 ... 60000
	 * @param channel The 1k thermocouple input channel number 1..16
	 * @return Returns input resistance in ohms
	 */
	int readRes1k(uint8_t channel);

	/*!
	 * @brief Read the value in ohms of one 10k thermocouple input channel, range 0 ... 60000
	 * @param channel The 10k thermocouple input channel number 1..16
	 * @return Returns input resistance in ohms
	 */
	int readRes10k(uint8_t channel);

	/*!
	 * @brief Read the value of one dry contact input.
	 * @param channel The dry contact input channel number 1..16
	 * @return Returns the dry contact input state as a boolean
	 */
	bool readDC(uint8_t channel);

	/*!
	 * @brief Read all dry contact inputs as 16bit integer
	 * @return Returns the bitmap of the inputs
	 */
	int readDC();

	/*!
	 * @brief Enable/Disable event counting function for on dry contact input channel
	 * @param channel The dry contact input channel number 1..16
	 * @param enable Turn on or off the counting false/true
	 * @return true if the operation succeed, false else
	 */
	bool cfgCounter(uint8_t channel, bool enable);

	/*!
	 * @brief Read the counter for a dry contact input channel
	 * @param channel The dry contact input channel number 1..16
	 * @return the counter as integer
	 */
	int readCounter(uint8_t channel);

	/*!
	 * @brief Reset the counter for a dry contact input channel
	 * @param channel The dry contact input channel number 1..16
	 * @return true if succed else false
	 */
	bool resetCounter(uint8_t channel);

private:
	uint8_t _hwAdd;
	bool _detected;
	TwoWire *_wire;
	int writeBuff(uint8_t add, uint8_t *buff, uint8_t size);
	int readBuff(uint8_t add, uint8_t *buff, uint8_t size);
	int writeByte(uint8_t add, uint8_t value);
	int writeWord(uint8_t add, uint16_t value);
	int writeDWord(uint8_t add, uint32_t value);
	int readByte(uint8_t add, uint8_t *value);
	int readWord(uint8_t add, uint16_t *value);
	int readDWord(uint8_t add, uint32_t *value);
	int readSignedDWord(uint8_t add, int32_t *value);
};

#endif //SM_HOME_H_
