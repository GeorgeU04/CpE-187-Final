/*
 * GT-U7.c
 *
 *  Created on: Jul 26, 2025
 *      Author: gjumb
 */
#include<stdint.h>
#include"main.h"
#include"GT-U7.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

//void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {
//	length = size;
//	HAL_UART_Transmit(&huart2, data, length,
//	HAL_MAX_DELAY);
//	data[size] = '\0';
//	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, data, UART_BUFFER);
//
//}
//
//void startGPSRead(uint8_t *data) {
//	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, data, UART_BUFFER);
//}

// This is a horrible way to do this. Very bad.
// The arbitrary cutoff works but is not great. DMA would be superior and save time.
void startGPSRead(uint8_t *data) {
	for (int i = 0; i < UART_BUFFER; i++) {
		if (HAL_UART_Receive(&huart1, &data[i], 1, 100) != HAL_OK) {
			data[i] = '?';
		}
	}

	data[UART_BUFFER] = '\0';
}

GPSData parseGPSData(uint8_t *data) {
	GPSData cords = { 0 };
	char latitudeChar;
	char longitudeChar;
	char *line = strtok((char*) data, "\r\n");
	while (line) {
		if (strstr((char*) line, "$GPGLL")) {
			char *tok = strtok(line, ",");
			double raw = 0;
			int32_t deg = 0;
			double min = 0;
			for (uint8_t i = 0; tok; ++i) {
				switch (i) {
				case 1:
					raw = atof(tok);
					deg = (int32_t) (raw / 100);
					min = raw - deg * 100;
					cords.latitude = deg + (min / 60.0);
					break;

				case 2:
					latitudeChar = *tok;
					if (latitudeChar == 'S')
						cords.latitude *= -1;
					break;

				case 3:
					raw = atof(tok);
					deg = (int32_t) (raw / 100);
					min = raw - deg * 100;
					cords.longitude = deg + (min / 60.0);
					break;

				case 4:
					longitudeChar = *tok;
					if (longitudeChar == 'W')
						cords.longitude *= -1;
					break;
				}
				tok = strtok(NULL, ",");
			}
		}
		line = strtok(NULL, "\r\n");
	}
	return cords;
}

