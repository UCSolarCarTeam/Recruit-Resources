#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_can.h"
#include "cmsis_os.h"

//TODO: Define an external CAN handle (same variable as in main)
CAN_HandleTypeDef hcan2;

//TODO: Define external CAN_Tx header (same variable as in main)
CAN_TxHeaderTypeDef CAN_TxHeader;

//TODO: Define external blue LED toggle flag (same variable as in main)
uint8_t blueToggleFlag;

void blueLedToggleTask(void const* arg);
