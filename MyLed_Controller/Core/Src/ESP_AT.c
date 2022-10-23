#include <ESP_AT.h>


char rx_buff[RX_BUFF_LENGTH];
char tx_buff[TX_BUFF_LENGTH];
int esp_response = -1;

int esp_message_WIFI_CONNECTED = 0;
int esp_message_WIFI_DISCONNECT = 0;
char esp_message_CONNECT[CONNECT_BUFF_LENGTH];
char esp_message_CLOSE[CLOSE_BUFF_LENGTH];
char esp_message_IDP[IDP_BUFF_LENGTH];

void ESP_AT_Init(){
	AT__RST_Execute();
	while(HAL_UARTEx_ReceiveToIdle_IT(H_UART_ESP, (uint8_t*)rx_buff, RX_BUFF_LENGTH) != HAL_OK);
}

ESP_Response AT_Execute(){
	sprintf(tx_buff, "%s", AT);
	return ESP_SendCommand();
}

ESP_Response ATE0_Execute(){
	sprintf(tx_buff, "%s", ATE0);
	return ESP_SendCommand();
}

ESP_Response AT__RST_Execute(){
	sprintf(tx_buff, "%s", AT__RST);
	HAL_UART_Transmit(H_UART_ESP, (uint8_t*)tx_buff, strlen(tx_buff), 100);
	HAL_Delay(500);
	return AT_OK;
}

ESP_Response AT__CWMODE_CUR_Set(uint8_t mode){
	char tmpstr[64];
	sprintf(tmpstr, "=%d", mode);
	sprintf(tx_buff, AT__CWMODE_CUR, tmpstr);
	return ESP_SendCommand();
}

ESP_Response AT__CIPAP_CUR_Set(char* ip, char* getaway, char* mask){
	char tmpstr[64];
	sprintf(tmpstr, "=\"%s\",\"%s\",\"%s\"", ip, getaway, mask);
	sprintf(tx_buff, AT__CIPAP_CUR, tmpstr);
	return ESP_SendCommand();
}

ESP_Response AT__CWSAP_CUR_Set(char* ssid, char* pwd, uint8_t chl, uint8_t ecn){
	char tmpstr[64];
	sprintf(tmpstr, "=\"%s\",\"%s\",%d,%d", ssid, pwd, chl, ecn);
	sprintf(tx_buff, AT__CWSAP_CUR, tmpstr);
	return ESP_SendCommand();
}

ESP_Response AT__CIPMUX_Set(uint8_t mode){
	char tmpstr[64];
	sprintf(tmpstr, "=%d", mode);
	sprintf(tx_buff, AT__CIPMUX, tmpstr);
	return ESP_SendCommand();
}

ESP_Response AT__CIPSERVER_Set(uint8_t mode, uint16_t port){
	char tmpstr[64];
	sprintf(tmpstr, "=%d,%d", mode, port);
	sprintf(tx_buff, AT__CIPSERVER, tmpstr);
	return ESP_SendCommand();
}

ESP_Response AT__CIPSTA_CUR_Set(char* ip, char* getaway, char* mask){
	char tmpstr[64];
	sprintf(tmpstr, "=\"%s\",\"%s\",\"%s\"", ip, getaway, mask);
	sprintf(tx_buff, AT__CIPSTA_CUR, tmpstr);
	return ESP_SendCommand();
}

ESP_Response AT__CWJAP_CUR_Set(char* ssid, char* pwd){
	char tmpstr[64];
	sprintf(tmpstr, "=\"%s\",\"%s\"", ssid, pwd);
	sprintf(tx_buff, AT__CWJAP_CUR, tmpstr);
	return ESP_SendCommand();
}

ESP_Response ESP_SendCommand(){
	memset(rx_buff, '\0', RX_BUFF_LENGTH);
	HAL_UART_Transmit(H_UART_ESP, (uint8_t*)tx_buff, strlen(tx_buff), 100);
	while(esp_response == -1){}
	ESP_Response tmp_resp = esp_response;
	esp_response = -1;
	return tmp_resp;
}

void ESP_CheckMessage(){
	if (esp_message_IDP[0] != '\0'){
		IPD_callback(esp_message_IDP);
		memset(esp_message_IDP, '\0', IDP_BUFF_LENGTH);
	}
	if(esp_message_WIFI_CONNECTED){
		WIFI_CONNECTED_callback();
		esp_message_WIFI_CONNECTED = 0;
	}
	else if(esp_message_WIFI_DISCONNECT){
		WIFI_DISCONNECT_callback();
		esp_message_WIFI_DISCONNECT = 0;
	}
	if(esp_message_CONNECT[0] != '\0'){
		CONNECT_callback(esp_message_CONNECT);
		memset(esp_message_CONNECT, '\0', CONNECT_BUFF_LENGTH);
	}
	if(esp_message_CLOSE[0] != '\0'){
		CLOSE_callback();
		memset(esp_message_CLOSE, '\0', CLOSE_BUFF_LENGTH);
	}
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	if(huart == H_UART_ESP){
		if(strstr(rx_buff, _OK)){
			esp_response = AT_OK;
		}
		else if(strstr(rx_buff, _ERROR)){
			esp_response = AT_ERROR;
		}
		else if(strstr(rx_buff, _FAIL)){
			esp_response =  AT_FAIL;
		}


		else if(strstr(rx_buff, _CONNECT)){
			memcpy(esp_message_CONNECT, rx_buff, CONNECT_BUFF_LENGTH);
		}
		else if(strstr(rx_buff, _IPD)){
			memcpy(esp_message_IDP, rx_buff, IDP_BUFF_LENGTH);
		}
		else if(strstr(rx_buff, _CLOSED)){
			memcpy(esp_message_CLOSE, rx_buff, CLOSE_BUFF_LENGTH);
		}
		else if(strstr(rx_buff, _WIFI_CONNECTED)){
			esp_message_WIFI_CONNECTED = 1;
		}
		else if(strstr(rx_buff, _WIFI_DISCONNECT)){
			esp_message_WIFI_DISCONNECT = 1;
		}
		memset(rx_buff, '\0', RX_BUFF_LENGTH);
		while(HAL_UARTEx_ReceiveToIdle_IT(H_UART_ESP, (uint8_t*)rx_buff, RX_BUFF_LENGTH) != HAL_OK);
	}
}

__weak void WIFI_CONNECTED_callback(){};
__weak void WIFI_DISCONNECT_callback(){};
__weak void CONNECT_callback(char* esp_message_CONNECT){};
__weak void CLOSE_callback(){};
__weak void IPD_callback(char* esp_message_IDP){}


