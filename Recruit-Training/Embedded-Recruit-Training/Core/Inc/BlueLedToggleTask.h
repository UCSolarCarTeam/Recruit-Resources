#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_can.h"
#include "cmsis_os.h"
#include "main.h"

//TODO: Define an external CAN handle (same variable as in main)
//TODO: Define external CAN_Tx header (same variable as in main)
//TODO: Define external blue LED toggle flag (same variable as in main)

void blueLedToggleTask(void const* arg);
extern CAN_HandleTypeDef hcan2;
extern CAN_TxHeaderTypeDef canHeader;
extern uint8_t blueToggleFlag;
