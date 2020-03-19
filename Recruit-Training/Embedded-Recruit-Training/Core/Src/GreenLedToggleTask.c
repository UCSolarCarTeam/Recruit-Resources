#include "GreenLedToggleTask.h"
static const GREEN_LED_STATUS_STDID = 0xDDD;
const TEN_HZ_TO_MS = 10000;

void greenLedToggleTask(void const* arg)
{
    static const GREEN_LED_TOGGLE_FREQ = TEN_HZ_TO_MS;
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg;

    for (;;)
    {
        osDelayUntil(prevWakeTime + GREEN_LED_TOGGLE_FREQ);  //TODO: Replace 1 with time period for delay
        //TODO: Check blue toggel flag and toggle blue LED
        if(greenFlag == 1)
        {
            //toggle green led, this requires a HAL GPIO Function
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
        }
        GPIO_PinState pinStatus = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
        //TODO: Send CAN message indicating current state of LED
        osStatus_t status = osMutexAcquire(canMutex, 1);

        while(status != osOK){
            status = osMutexAcquire(canMutex, 1);
        }

        HAL_CAN_GetTxMailboxesFreeLevel(&hcan2); 
        uint8_t data[1] = {0};
        uint32_t mailbox; //should this be equal to the value HAL_CAN_GetTxMailboxesFreeLevel(hcan2) ? 
        CANTxHeader.StdId = GREEN_LED_STATUS_STDID;
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
