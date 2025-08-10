/*
 * GT-U7.h
 *
 *  Created on: Jul 26, 2025
 *      Author: gjumb
 */

#ifndef INC_GT_U7_H_
#define INC_GT_U7_H_

#define UART_BUFFER 500


typedef struct {
	float latitude;
	float longitude;
} GPSData;

void startGPSRead(uint8_t *data);
GPSData parseGPSData(uint8_t *str);

#endif /* INC_GT_U7_H_ */
