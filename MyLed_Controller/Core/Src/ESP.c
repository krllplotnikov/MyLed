#ifndef SRC_ESP_C_
#define SRC_ESP_C_

#include "ESP.h"

ESP_Response ESP_Init(){
	AT__RST_Execute();
	ESP_AT_Init();
	AT_Execute();
	return ATE0_Execute();
}

ESP_Response ESP_STAAP_Mode(){
	return AT__CWMODE_CUR_Set(3);
}

ESP_Response ESP_AP_Mode(){
	return AT__CWMODE_CUR_Set(2);
}

ESP_Response ESP_SetAPIP(char* ip, char* getaway, char* mask){
	return AT__CIPAP_CUR_Set(ip, getaway, mask);
}

ESP_Response ESP_APconfig(char* ssid, char* pwd, uint8_t chl, uint8_t ecn){
	return AT__CWSAP_CUR_Set(ssid, pwd, chl, ecn);
}


ESP_Response ESP_STA_Mode(){
	return AT__CWMODE_CUR_Set(1);
}

ESP_Response ESP_SetSTAIP(char* ip, char* getaway, char* mask){
	return AT__CIPSTA_CUR_Set(ip, getaway, mask);
}

ESP_Response ESP_WiFi(char* ssid, char* pwd){
	return AT__CWJAP_CUR_Set(ssid, pwd);
}

ESP_Response ESP_StartTCPServer(uint16_t port){
	AT__CIPMUX_Set(1);
	return AT__CIPSERVER_Set(1, port);
}

#endif /* SRC_ESP_C_ */
