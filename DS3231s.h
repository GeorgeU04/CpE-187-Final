/*
 * DS3231s.h
 *
 *  Created on: Jul 25, 2025
 *      Author: gjumb
 */

#ifndef INC_DS3231S_H_
#define INC_DS3231S_H_

#define DS3231_ADDRESS  (0x68 << 1)

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t isPM;
	uint8_t is12Mode;
	uint8_t day;
} RTC_DS3231s;

void setTime(void);
void readTimeData(uint8_t *time);
RTC_DS3231s parseTime(uint8_t *time);

#endif /* INC_DS3231S_H_ */
