# Sequent-16univin-Library
Arduino library for Sequent Microsystems [Sixteen Analog/Digital Inputs 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/collections/all-io-cards/products/sixteen-analog-digital-inputs-8-layer-stackable-hat-for-raspberry-pi)

## Install
### Library manager
Go to **Tools**>>**Manage Libraries..** menu and search for *SM_16UNIVIN* and click install 
### Manual install
To download click <>Code > [Download ZIP](https://github.com/SequentMicrosystems/Sequent-16univin-Library/archive/refs/heads/main.zip) button from the main [page](https://github.com/SequentMicrosystems/Sequent-16univin-Library), rename the uncompressed folder to "SM_16univin" 
and copy to the libraries subdirectory of your sketchbook directory ("This PC > Documents > Arduino > libraries" for a Windows PC
 or "Home > arduino > libraries" on Linux PC). Now launch the Arduino environment. If you open the Sketch > Include Library menu, you should see Sequent 16univin inside. 
 The library will be compiled with sketches that use it. Open an arduino sketch, go to File > Examples > Seqquent 16univin > and chose your example to run.

## Usage
There are three ways to control the Sexteen Universal Inputs Card from the Arduino environment.

### Method 1: Using any Arduino controller
You can use this method with any Arduino card with an I2C port by connecting I2C-SDA, I2C-SCL, +5V and GND, as shown in the following table.
      
| SIGNAL | PIN# |CONN| PIN# | SIGNAL|
|---|---|---|---|---|
| | --1 | O - O | 2-- |  +5V | 
| I2C-SDA | --3| O - O | 4-- |  +5V |
| I2C-SCL |-- 5|O - O| 6--|  GND |
|  |-- 7|O - O| 8--||
| GND |-- 9|O - O|10--||
| |--11|O - O|12--||
| |--13|O - O|14--| GND|
| |--15|O - O|16--||
||--17|O - O|18--||
||--19|O - O|20--|  GND|
||--21|O - O|22--||
||--23|O - O|24--||
|GND |--25|O - O|26--||
||--27|O - O|28--||
||--29|O - O|30--|  GND|
||--31|O - O|32--||
||--33|O - O|34--|  GND|
||--35|O - O|36--||
||--37|O - O|38--||
|GND |--39|O - O|40--||
 
### Method 2: Using the SM Arduino Raspberry Pi Replacement Kit
Sequent Microsystems [Arduino Uno, Nano, Teensy, Feather or ESP32 Raspberry Pi Replacement Kit](https://sequentmicrosystems.com/products/raspberry-pi-replacement-card) is an inexpensive adapter which can be used to control any of our HATs using Uno, Nano, Teensy, Feather or ESP32. Plug the Home Automation HAT into the 40 pin connector of the adapter and write your Arduino software.

### Method 3: Using the SM ESP32-Pi Raspberry Pi Alternative Card
ESP32-Pi is a Raspberry Pi alternate solution which can control directly the Sexteen Universal Inputs HAT.
In your sketchbook set the board type to DOIT ESP32 DEVKIT V1: Tool >> Board >> ESP32 Arduino >> DOIT ESP32 DEVKIT V1

## Functions prototypes
	
	/*!
	 * @brief Class constructor
	 * @param stack - stack level setted from the dip-switches on the card
	 */
	SM_16_UNIVIN(uint8_t stack = 0);
	
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
