#include "ESP_AT.h"

UART_HandleTypeDef* m_uart;

uint8_t rxBuffer[RX_BUFFER_SIZE] = {};
uint8_t txBuffer[TX_BUFFER_SIZE] = {};

__weak void ESP_IPD_Callback(uint8_t id, uint16_t len, char* data){}

uint8_t ESP_Init(UART_HandleTypeDef* uart){
	m_uart = uart;
	ESP_Reset();
	ESP_ATE0();
	return 1;
}

uint8_t ESP_ATE0(){
	uint8_t returnCode = 0;
	uint16_t rxLen = 0;
	sprintf((char*)txBuffer, "ATE0\r\n");
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 100);
	if(strstr((char*)rxBuffer, "\r\nOK\r\n")){
		returnCode = 1;
	} else returnCode = 0;
	memset(txBuffer, 0, TX_BUFFER_SIZE);
	memset(rxBuffer, 0, RX_BUFFER_SIZE);
	return returnCode;
}
uint8_t ESP_Reset(){
	uint8_t returnCode = 0;
	uint16_t rxLen = 0;
	uint8_t receiveCounter = 0;

	sprintf((char*)txBuffer, "AT+RST\r\n");
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 100);
	if(!strstr((char*)rxBuffer, "\r\nOK\r\n")){
		return returnCode;
	}

	receiveAgain:
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 500);
	if(strstr((char*)rxBuffer, "\r\nready\r\n")){
		returnCode = 1;
	} else if(receiveCounter < 10){
		receiveCounter++;
		goto receiveAgain;
	} else{
		returnCode = 0;
	}
	memset(txBuffer, 0, TX_BUFFER_SIZE);
	memset(rxBuffer, 0, RX_BUFFER_SIZE);
	return returnCode;
}

uint8_t ESP_AP_Mode(){
	uint8_t returnCode = 0;
	uint16_t rxLen = 0;

	sprintf((char*)txBuffer, "AT+CWMODE_CUR=2\r\n");
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 1000);
	if(strstr((char*)rxBuffer, "\r\nOK\r\n")){
		returnCode = 1;
	} else returnCode = 0;
	memset(txBuffer, 0, TX_BUFFER_SIZE);
	memset(rxBuffer, 0, RX_BUFFER_SIZE);
	return returnCode;
}

uint8_t ESP_AP_Config(char* ssid, char* pwd, uint8_t chl, uint8_t ecn){
	uint8_t returnCode = 0;
	uint16_t rxLen = 0;

	sprintf((char*)txBuffer, "AT+CWSAP_CUR=\"%s\",\"%s\",%d,%d\r\n", ssid, pwd, chl, ecn);
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 1000);
	if(strstr((char*)rxBuffer, "\r\nOK\r\n")){
		returnCode = 1;
	} else returnCode = 0;
	memset(txBuffer, 0, TX_BUFFER_SIZE);
	memset(rxBuffer, 0, RX_BUFFER_SIZE);
	return returnCode;
}

uint8_t ESP_AP_IP(char* ip, char* getaway, char* mask){
	uint8_t returnCode = 0;
	uint16_t rxLen = 0;

	sprintf((char*)txBuffer, "AT+CIPAP_CUR=\"%s\",\"%s\",\"%s\"\r\n", ip, getaway, mask);
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 1000);
	if(strstr((char*)rxBuffer, "\r\nOK\r\n")){
		returnCode = 1;
	} else returnCode = 0;
	memset(txBuffer, 0, TX_BUFFER_SIZE);
	memset(rxBuffer, 0, RX_BUFFER_SIZE);
	return returnCode;
}

uint8_t ESP_STA_Mode(){
	uint8_t returnCode = 0;
	uint16_t rxLen = 0;

	sprintf((char*)txBuffer, "AT+CWMODE_CUR=1\r\n");
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 1000);
	if(strstr((char*)rxBuffer, "\r\nOK\r\n")){
		returnCode = 1;
	} else returnCode = 0;
	memset(txBuffer, 0, TX_BUFFER_SIZE);
	memset(rxBuffer, 0, RX_BUFFER_SIZE);
	return returnCode;
}

uint8_t ESP_STA_IP(char* ip, char* getaway, char* mask){
	uint8_t returnCode = 0;
	uint16_t rxLen = 0;

	sprintf((char*)txBuffer, "AT+CIPSTA_CUR=\"%s\",\"%s\",\"%s\"\r\n", ip, getaway, mask);
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 1000);
	if(strstr((char*)rxBuffer, "\r\nOK\r\n")){
		returnCode = 1;
	} else returnCode = 0;
	memset(txBuffer, 0, TX_BUFFER_SIZE);
	memset(rxBuffer, 0, RX_BUFFER_SIZE);
	return returnCode;
}
uint8_t ESP_ConnectToAP(char* ssid, char* pwd){
	uint8_t receiveCounter = 0;
	uint8_t returnCode = 0;
	uint16_t rxLen = 0;

	sprintf((char*)txBuffer, "AT+CWJAP_CUR=\"%s\",\"%s\"\r\n", ssid, pwd);
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);

	receiveAgain:
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 15000);
	if(strstr((char*)rxBuffer, "\r\nOK\r\n")){
		returnCode = 1;
	} else if(strstr((char*)rxBuffer, "\r\nFAIL\r\n")){
		returnCode = 0;
	} else if(receiveCounter < 3){
		receiveCounter++;
		goto receiveAgain;
	} else{
		returnCode = 0;
	}

	memset(txBuffer, 0, TX_BUFFER_SIZE);
	memset(rxBuffer, 0, RX_BUFFER_SIZE);
	return returnCode;
}

uint8_t ESP_StartTCPServer(uint16_t port){
	uint8_t returnCode = 0;
	uint16_t rxLen = 0;

	sprintf((char*)txBuffer, "AT+CIPMUX=1\r\n");
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 1000);
	if(!strstr((char*)rxBuffer, "\r\nOK\r\n")){
		return returnCode;
	}

	sprintf((char*)txBuffer, "AT+CIPSERVER=1,%d\r\n", port);
	HAL_UART_Transmit(m_uart, txBuffer, strlen((char*)txBuffer), 100);
	HAL_UARTEx_ReceiveToIdle(m_uart, rxBuffer, RX_BUFFER_SIZE, &rxLen, 1000);
	if(strstr((char*)rxBuffer, "\r\nOK\r\n")){
		returnCode = 1;
	} else returnCode = 0;

	memset(txBuffer, 0, TX_BUFFER_SIZE);
	memset(rxBuffer, 0, RX_BUFFER_SIZE);
	return returnCode;
}

void ESP_EnableCallbacs(){
	while(HAL_UARTEx_ReceiveToIdle_IT(m_uart, rxBuffer, RX_BUFFER_SIZE) != HAL_OK);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart == m_uart)
    {
    	char* idpIdx, *idIdx, *lenIdx, *dataIdx;
    	uint8_t id;
    	uint16_t len;
    	idpIdx = strstr((char*)rxBuffer, "+IPD");
    	dataIdx = strchr((char*)rxBuffer, ':') + 1;
    	if(idpIdx != NULL){
        	idIdx = idpIdx + 5;
        	lenIdx = idpIdx + 7;
        	id = atoi(idIdx);
        	len = atoi(lenIdx);
        	ESP_IPD_Callback(id, len, dataIdx);
    	}

    	memset(rxBuffer, 0, RX_BUFFER_SIZE);
    	while(HAL_UARTEx_ReceiveToIdle_IT(m_uart, rxBuffer, RX_BUFFER_SIZE) != HAL_OK);
    }
}
