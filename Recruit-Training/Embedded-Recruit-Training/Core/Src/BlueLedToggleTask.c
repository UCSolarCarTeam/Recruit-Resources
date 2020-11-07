#include "BlueLedToggleTask.h"

static const uint32_t BLUE_LED_STATUS_STDID = 0xCCC;
static const uint32_t BLUE_LED_TOGGLE_FREQ = 1000; 

void blueLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg; // Get mutex that was passed as an argument

    for (;;)
    {
        //TODO: Add BLUE_LED_TOGGLE_FREQ to prevWakeTime
       
        prevWakeTime += BLUE_LED_TOGGLE_FREQ; // this increments blue toggle with the +=
        osDelayUntil(prevWakeTime);
        
        //TODO: Check blue toggle flag and toggle blue LED
        if(BlueToggleLED)
        {
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            
        }

       uint8_t pinState_of_blue_LED = HAL_GPIO_ReadPin(LED_RED_GPIO_Port, LED_RED_Pin);
        // this is to read the value of the GPIO function and whatever it reads, since it has a return value, what the value is of the GPIO function will be put into the pinState variable of type uint8_t which is like a boolean 

        
        //TODO: Send CAN message indicating current state of LED

        
        if(osMutexAcquire(canMutex, 0) == HAL_OK)
        {
            if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) > 0)
            {
                uint8_t data_array[1];

                uint32_t mailbox_variable;

                CANTxHeader.StdId = BLUE_LED_STATUS_STDID;
                CANTxHeader.DLC = 1;
                data_array[0] = !pinState_of_blue_LED;

                HAL_CAN_AddTxMessage(&hcan2, &CANTxHeader, &data_array, &mailbox_variable);
                
            }
        
        }

       osMutexRelease(canMutex);

    }
}
