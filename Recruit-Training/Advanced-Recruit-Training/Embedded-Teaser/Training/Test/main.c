#include <stdio.h>
#include "unity.h"
#include "TrainingTest.h"

void setUp(void)
{
}

void tearDown(void)
{
}

int main(void)
{
    UNITY_BEGIN();

    runTrainingTests();

    return UNITY_END();
}