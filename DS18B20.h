/*
 * DS18B20.h
 *
 *  Created on: Jul 25, 2025
 *      Author: gjumb
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#include<stdint.h>

#define DS18B20_PORT GPIOB
#define DS18B20_PIN 4

void writeBit(uint8_t bit);
void writeByte(uint8_t byte);
uint8_t readBit(void);
uint8_t readByte(void);
uint8_t sendReset(void);
void startConversion(void);
float readTemperature(void);

#endif /* INC_DS18B20_H_ */
