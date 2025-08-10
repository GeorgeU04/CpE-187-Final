/*
 * LCD.c
 *
 *  Created on: Jul 25, 2025
 *      Author: gjumb
 */

#include"LCD.h"
#include<stdint.h>
#include "main.h"


void LCDSendCMD(uint8_t cmd) {
	uint8_t lower = (cmd << 4) & 0xf0;
	uint8_t upper = (cmd & 0xf0);
	uint8_t data[4];
	data[0] = upper | 0x0C;
	data[1] = upper | 0x08;
	data[2] = lower | 0x0C;
	data[3] = lower | 0x08;
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS, data, 4, HAL_MAX_DELAY);
}

void LCDSendData(uint8_t input) {
	uint8_t data[4];
	uint8_t upper = (input & 0xf0);
	uint8_t lower = ((input << 4) & 0xf0);
	data[0] = upper | 0x0D;
	data[1] = upper | 0x09;
	data[2] = lower | 0x0D;
	data[3] = lower | 0x09;
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS, data, 4, HAL_MAX_DELAY);
}

void LCDInit(void) {
	HAL_Delay(16);
	LCDSendCMD(0x30);
	HAL_Delay(5);
	LCDSendCMD(0x30);
	HAL_Delay(1);
	LCDSendCMD(0x30);
	HAL_Delay(10);
	LCDSendCMD(0x20);
	HAL_Delay(10);
	LCDSendCMD(0x28);
	HAL_Delay(1);
	LCDSendCMD(0x08);
	HAL_Delay(1);
	LCDSendCMD(0x01);
	HAL_Delay(2);
	LCDSendCMD(0x06);
	HAL_Delay(1);
	LCDSendCMD(0x0C);
	HAL_Delay(1);
}

void LCDSendString(char *str) {
	while (*str)
		LCDSendData(*str++);
}

void LCDSetCursor(uint8_t row, uint8_t col) {
	if (row) {
		col |= 0xC0;
	} else {
		col = 0x80;
	}
	LCDSendCMD(col);
}

void LCDClear(void) {
	LCDSendCMD(0x01);
	HAL_Delay(2);
	LCDSendCMD(0x0C);
	HAL_Delay(1);
}
