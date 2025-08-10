/*
 * DS3231s.c
 *
 *  Created on: Jul 25, 2025
 *      Author: gjumb
 */

#include<stdint.h>
#include"DS3231s.h"
#include "main.h"


// only used to sync; not really needed anymore
void setTime(void) {
	uint8_t time[1];

	//time[0] = ((second / 10) << 4) | (second % 10);
	//time[1] = ((minute / 10) << 4) | (minute % 10);
	//time[0] = 0b00000000;
	time[0] = 0b00000110;

	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x03, I2C_MEMADD_SIZE_8BIT, time,
			1, HAL_MAX_DELAY);
}

void readTimeData(uint8_t *time) {
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, time,
			4, HAL_MAX_DELAY);
}

RTC_DS3231s parseTime(uint8_t *time) {
	RTC_DS3231s clock = { 0 };
	uint8_t seconds = 0;
	uint8_t minutes = 0;
	uint8_t hours = 0;
	// Seconds
	seconds = ((time[0] >> 4) * 10) + (time[0] & 0b1111);
	clock.seconds = seconds;
	// Minutes
	minutes = ((time[1] >> 4) * 10) + (time[1] & 0b1111);
	clock.minutes = minutes;
	// Hours
	if (time[2] & 0b01000000) { // 12 hour
		clock.is12Mode = 1;
		clock.isPM = time[2] & 0b00100000 ? 1 : 0;
		hours = (((time[2] & 0b11111) >> 4) * 10) + (time[2] & 0b1111);
		clock.hours = hours;
	} else { // 24 hour
		hours = ((time[2] >> 4) * 10) + (time[2] & 0b1111);
		clock.hours = hours;
		clock.isPM = 0;
		clock.is12Mode = 0;
	}
	// Day
	clock.day = time[3];
	return clock;
}
