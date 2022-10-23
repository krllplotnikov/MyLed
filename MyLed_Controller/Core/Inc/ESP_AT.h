#ifndef INC_ESP_AT_H_
#define INC_ESP_AT_H_

#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdio.h"


//Async, 115200, 8bit
extern UART_HandleTypeDef huart1;
#define H_UART_ESP (&huart1)

#define RX_BUFF_LENGTH 256
#define TX_BUFF_LENGTH 256

//--------Responses------
#define _OK "\r\nOK\r\n"
#define _ERROR "\r\nERROR\r\n"
#define _FAIL "\r\nFAIL\r\n"
//--------Messages--------

#define _WIFI_CONNECTED "WIFI CONNECTED"
#define _WIFI_DISCONNECT "WIFI DISCONNECT"
#define _CONNECT ",CONNECT"
#define _CLOSED ",CLOSED"
#define _IPD "+IPD"

#define CONNECT_BUFF_LENGTH 16
#define CLOSE_BUFF_LENGTH 16
#define IDP_BUFF_LENGTH 256

typedef enum{
	AT_OK,
	AT_ERROR,
	AT_FAIL
}ESP_Response;
//-------------COMMANDS-------
#define AT "AT\r\n"
#define ATE0 "ATE0\r\n"
#define AT__RST "AT+RST\r\n"
#define AT__CWMODE_CUR "AT+CWMODE_CUR%s\r\n"
#define AT__CIPAP_CUR "AT+CIPAP_CUR%s\r\n"
#define AT__CIPSTA_CUR "AT+CIPSTA_CUR%s\r\n"
#define AT__CWSAP_CUR "AT+CWSAP_CUR%s\r\n"
#define AT__CWJAP_CUR "AT+CWJAP_CUR%s\r\n"
#define AT__CIPMUX "AT+CIPMUX%s\r\n"
#define AT__CIPSERVER "AT+CIPSERVER%s\r\n"

void ESP_AT_Init();
ESP_Response AT_Execute();
ESP_Response ATE0_Execute();
ESP_Response AT__RST_Execute();
ESP_Response AT__CWMODE_CUR_Set(uint8_t mode);
ESP_Response AT__CIPAP_CUR_Set(char* ip, char* getaway, char* mask);
ESP_Response AT__CWSAP_CUR_Set(char* ssid, char* pwd, uint8_t chl, uint8_t ecn);
ESP_Response AT__CIPMUX_Set(uint8_t mode);
ESP_Response AT__CIPSERVER_Set(uint8_t mode, uint16_t port);
ESP_Response AT__CIPSTA_CUR_Set(char* ip, char* getaway, char* mask);
ESP_Response AT__CWJAP_CUR_Set(char* ssid, char* pwd);

ESP_Response ESP_SendCommand();

void ESP_CheckMessage();

void WIFI_CONNECTED_callback();
void WIFI_DISCONNECT_callback();
void CONNECT_callback(char* esp_message_CONNECT);
void CLOSE_callback();
void IPD_callback(char* esp_message_IDP);
#endif
