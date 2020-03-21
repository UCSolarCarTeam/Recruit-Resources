#include "GreenLedToggleTask.h"

static const uint32_t GREEN_LED_STATUS_STDID = 0xDDD;
static const uint32_t GREEN_LED_TOGGLE_FREQ = 10000;

void greenLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg;

    for (;;)
    {
        osDelayUntil(prevWakeTime + GREEN_LED_TOGGLE_FREQ);  //TODO: Replace 1 with time period for delay
       
        //TODO: Check green toggle flag and toggle green LED
        if (greenToggleFlag)
        {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
        }
        
        GPIO_PinState greenStatus = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);

        //TODO: Send CAN message indicating current state of LED
        while (osMutexAcquire(canMutex, 0) != osOK) {}

        if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan2))    
        {
            uint8_t data[1] = {0};
            uint32_t mailbox;
            
            CAN_TxHeader.StdId = GREEN_LED_STATUS_STDID;
            CAN_TxHeader.DLC = 1;
                
            if (greenStatus == 0)
            {
                data[0] = 1;
            }
            else if (greenStatus == 1)
            {
                data[0] = 0;
            }

            HAL_CAN_AddTxMessage(&hcan2, &CAN_TxHeader, &data, &mailbox);
        }
        
        osMutexRelease(canMutex);
    }
}
