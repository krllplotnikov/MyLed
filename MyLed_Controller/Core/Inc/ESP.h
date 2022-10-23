#ifndef INC_ESP_H_
#define INC_ESP_H_

#include "ESP_AT.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

ESP_Response ESP_Init();
ESP_Response ESP_STAAP_Mode();
ESP_Response ESP_AP_Mode();
ESP_Response ESP_APconfig(char* ssid, char* pwd, uint8_t chl, uint8_t ecn);
ESP_Response ESP_STA_Mode();
ESP_Response ESP_SetAPIP(char* ip, char* getaway, char* mask);
ESP_Response ESP_SetSTAIP(char* ip, char* getaway, char* mask);
ESP_Response ESP_WiFi(char* ssid, char* pwd);
ESP_Response ESP_StartTCPServer(uint16_t port);

#endif /* INC_ESP_H_ */
