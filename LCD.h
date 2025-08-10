/*
 * LCD.h
 *
 *  Created on: Jul 25, 2025
 *      Author: gjumb
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include<stdint.h>

#define LCD_ADDRESS (0x27 << 1)

void LCDSendCMD(uint8_t cmd);
void LCDSendData(uint8_t input);
void LCDInit(void);
void LCDSendString(char *str);
void LCDSetCursor(uint8_t row, uint8_t col);
void LCDClear(void);

#endif /* INC_LCD_H_ */
