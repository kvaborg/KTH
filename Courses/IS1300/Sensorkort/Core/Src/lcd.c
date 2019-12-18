/**
 *****************************************************
 @brief lcd, lcd library functions
 @file lcd.c
 @author Alexander Borg
 @version 1.0
 @date 28-November-2019
 @brief Source code for EA DOGS104W-A LCD
 *****************************************************
 */

#include "lcd.h"

/**
@brief lcd_init, inits the lcd through a series of instructions
@param void, no parameters
@return void, no return value
 */
void lcd_init() {

	HAL_GPIO_WritePin(Disp_Reset_GPIO_Port, Disp_Reset_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(Disp_Reset_GPIO_Port, Disp_Reset_Pin, GPIO_PIN_SET);
	HAL_Delay(100);

	lcd_write_instr(0x3A);	//8-Bit data length extension Bit RE=1; REV=0
	lcd_write_instr(0x09);	//4 line display
	lcd_write_instr(0x06);	//Bottom view
	lcd_write_instr(0x1E);	//Bias setting BS1=1
	lcd_write_instr(0x39);	//8-Bit data length extension Bit RE=0; IS=1
	lcd_write_instr(0x1B);	//BS0=1 -> Bias=1/6
	lcd_write_instr(0x6E); //Devider on and set value
	lcd_write_instr(0x56); //Booster on and set contrast (BB1=C5, DB0=C4)
	lcd_write_instr(0x7A); //Set contrast (DB3-DB0=C3-C0)
	lcd_write_instr(0x38); //8 bit data length extension Bit RE=0; IS=0

	lcd_clear();
	lcd_set_ROM(ROMA);
	lcd_on_off(DISPLAY_ON);
}

/**
@brief lcd_write_instr, writes instructions to the LCD. RS = 0, R/W = 0
@param uint8_t, the instruction to send to the LCD
@return void, no return value
 */
void lcd_write_instr(uint8_t instr) {
	uint8_t start_byte = 0x1F;
	uint8_t lower_data = (instr & 0x0F);
	uint8_t higher_data = ((instr >> 4) & 0x0F);

	static uint8_t instr_buffer[MAX_BUFFER_SIZE];
	instr_buffer[0] = start_byte;
	instr_buffer[1] = lower_data;
	instr_buffer[2] = higher_data;

	if(HAL_SPI_STATE_READY) {
		HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
		HAL_Delay(5);

		HAL_SPI_Transmit(&hspi2, instr_buffer, MAX_BUFFER_SIZE, 100);

		HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
	}
}

/**
@brief lcd_write_data, writes data to the LCD, RS = 1 R/W = 1
@param uint8_t, data to write to the LCD
@return void, no return value
 */
void lcd_write_data(uint8_t data) {

	uint8_t start_byte = 0x5F;					//Send 5 synchronisation bits, RS = 1, R/W = 0
	uint8_t lower_data = (data & 0x0F);			//send lower data bits
	uint8_t higher_data = ((data>>4) & 0x0F);	//send higher data bits

	static uint8_t data_buffer[MAX_BUFFER_SIZE];
	data_buffer[0] = start_byte;
	data_buffer[1] = lower_data;
	data_buffer[2] = higher_data;

	if(HAL_SPI_STATE_READY) {
		HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
		HAL_Delay(5);

		HAL_SPI_Transmit(&hspi2, data_buffer, MAX_BUFFER_SIZE, 100);

		HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
	}
}

/**
@brief lcd_clear, clears the display and sets the cursor position on line 1
@param void, no parameters
@return void, no return value
 */
void lcd_clear()
{
	lcd_write_instr(0x01);
	lcd_set_pos(LINE1);
}

/**
@brief lcd_set_pos, sets position of cursor
@param uint8_t, the position
@return void, no return value
 */
void lcd_set_pos(uint8_t pos) {
	lcd_write_instr(LCD_HOME_L1+pos);
}

/**
@brief lcd_write_char, writes a charachter to the LCD
@param uint8_t, the character to write to the LCD
@return void, no return value
 */
void lcd_write_char(int8_t ch) {
	lcd_write_data(ch);
}

/**
@brief lcd_write_string, writes a string to the LCD
@param string, pointer to the string to write
@return void, no return value
 */
void lcd_write_string(char * string) {
	do
	{
		lcd_write_data(*string++);
	}
	while(*string);
}

/**
@brief lcd_on_off, turns the display on or off
@param data, pointer to the string to write
@return void, no return value
 */
void lcd_on_off(uint8_t data) {
	lcd_write_instr(0x08+data);
}

/**
@brief lcd_set_contrast, sets the contrast on the LCD
@param uint8_t, contrast value (DB3-DB0=C3-C0)
@return void, no return value
 */
void lcd_set_contrast(uint8_t contr) {
	lcd_write_instr(0x39);
	lcd_write_instr(0x54 | (contr >> 4));
	lcd_write_instr(0x70 | (contr & 0x0F));
	lcd_write_instr(0x38);
}

/**
@brief lcd_set_ROM, sets the character set (ROMA=0x00, ROMB=0x04, ROMC=0x0C)
@param uint8_t, ROM to select.
@return void, no return value
 */
void lcd_set_ROM(uint8_t rom) {
	lcd_write_instr(0x3A);
	lcd_write_instr(0x72);
	lcd_write_data(rom);
	lcd_write_instr(0x38);
}




