#include "lcd.h"

void display_init() {
	write_instr(0x3A);	//8-Bit data length extension Bit RE=1; REV=0
	write_instr(0x09);	//4 line display
	write_instr(0x06);	//Bottom view
	write_instr(0x1E);	//Bias setting BS1=1
	write_instr(0x39);	//8-Bit data length extension Bit RE=0; IS=1
	write_instr(0x1B);	//BS0=1 -> Bias=1/6
	write_instr(0x6E); //Devider on and set value
	write_instr(0x56); //Booster on and set contrast (BB1=C5, DB0=C4)
	write_instr(0x7A); //Set contrast (DB3-DB0=C3-C0)
	write_instr(0x38); //Set contrast (DB3-DB0=C3-C0)
	write_instr(0x0F); //Display on, Cursor on, blink on
}

void write_instr(char instr) {
	unsigned char start_byte = 0x1F;
	unsigned char lower_data = (instr & 0x0F);
	unsigned char higher_data = ((instr >> 4) & 0x0F);

	unsigned char *start_ptr = &start_byte;
	unsigned char *lower_ptr = &lower_data;
	unsigned char *higher_ptr = &higher_data;

	HAL_SPI_Transmit(&hspi2, start_ptr, 8, 100);
	HAL_SPI_Transmit(&hspi2, lower_ptr, 8, 100);
	HAL_SPI_Transmit(&hspi2, higher_ptr, 8, 100);
}

void write_to_disp() {

}
