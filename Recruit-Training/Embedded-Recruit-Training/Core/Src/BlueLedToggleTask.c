#include "BlueLedToggleTask.h"
static const BLUE_LED_STATUS_STDID = 0xCCC;
const ONE_HZ_TO_MS = 1000;

void blueLedToggleTask(void const* arg)
{
    static const BLUE_LED_TOGGLE_FREQ = ONE_HZ_TO_MS;
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg; // Get mutex that was passed as an argument

    for (;;)
    {
        osDelayUntil(prevWakeTime + BLUE_LED_TOGGLE_FREQ);  //TODO: Replace 1 with time period for delay
        //TODO: Check blue toggle flag and toggle blue LED
        if(blueFlag == 1)
        {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        }
        GPIO_PinState pinStatus = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
        //TODO: Send CAN message indicating current state of LED
        osStatus_t status = osMutexAcquire(canMutex, 1);
        while(status != osOK){
            status = osMutexAcquire(canMutex, 1);
        }

        HAL_CAN_GetTxMailboxesFreeLevel(&hcan2); 
        uint8_t data[1] = {0};
        uint32_t mailbox; 
        CANTxHeader.StdId = BLUE_LED_STATUS_STDID;
        CANTxHeader.DLC = 1;
        
        if(pinStatus == 0)
        {
            data[0] = 1;
        }
        if(pinStatus == 1)
        {
            data[0] = 0;
        }
        
        HAL_CAN_AddTxMessage(&hcan2, &CANTxHeader, &data, &mailbox);
        osMutexRelease(canMutex); 
    }
}
