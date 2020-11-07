#include "GreenLedToggleTask.h"

void greenLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg;

    for (;;)
    {
        //TODO: Add GREEN_LED_TOGGLE_FREQ to prevWakeTime
        osDelayUntil(prevWakeTime);
        //TODO: Check blue toggel flag and toggle blue LED
        //TODO: Send CAN message indicating current state of LED
    }
}
