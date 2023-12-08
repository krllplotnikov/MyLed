#ifndef INC_ESP_AT_H_
#define INC_ESP_AT_H_

#include "stm32f1xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define RX_BUFFER_SIZE 256
#define TX_BUFFER_SIZE 256

uint8_t ESP_Init(UART_HandleTypeDef* uart);
uint8_t ESP_Reset();
uint8_t ESP_ATE0();
uint8_t ESP_AP_Mode();
uint8_t ESP_AP_Config(char* ssid, char* pwd, uint8_t chl, uint8_t ecn);
uint8_t ESP_AP_IP(char* ip, char* getaway, char* mask);
uint8_t ESP_STA_Mode();
uint8_t ESP_STA_IP(char* ip, char* getaway, char* mask);
uint8_t ESP_ConnectToAP(char* ssid, char* pwd);
uint8_t ESP_StartTCPServer(uint16_t port);

void ESP_EnableCallbacs();

void ESP_IPD_Callback(uint8_t id, uint16_t len, char* data);

#endif /* INC_ESP_AT_H_ */
