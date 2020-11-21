#include "unity.h"
#include "TrainingTest.h"
#include "Training.h"

void runTrainingTests()
{
    // Run all the tests here using RUN_TEST()
    RUN_TEST(test_EverythingValid);
    RUN_TEST(test_EverythingInvalid);
    RUN_TEST(test_OnlyLightsInvalid);
    RUN_TEST(test_OnlyMotorsInvalid);

}

void test_EverythingValid()
{
    uint8_t input[3] = {0b11111110, 0b11111110, 0b01111100};
    uint8_t expectedValidData = 0b111;
    uint8_t expectedOutput[3] = {input[0], input[1], input[2]};

    trainingTask(input);
    TEST_ASSERT_EQUAL_MESSAGE(expectedValidData,validData, "validData and its expected value doesnt match");
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expectedOutput, outputArray, 3, "Arrays don't match");

}

void test_EverythingInvalid()
{
    uint8_t input[3] = {0b00111110, 0b01111110, 0b01110101};
    uint8_t expectedValidData = 0b000;
    uint8_t expectedOutput[3] = {outputArray[0], outputArray[1], outputArray[2]};
    
    trainingTask(input);
    TEST_ASSERT_EQUAL_MESSAGE(expectedValidData,validData, "validData and its expected value doesnt match");
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expectedOutput, outputArray, 3, "Arrays don't match");

}

void test_OnlyLightsInvalid()
{
    uint8_t input[3] = {0b10000000, 0b10000000, 0b01011100};
    uint8_t expectedValidData = 0b011;
    uint8_t expectedOutput[3] = {input[0], input[1], outputArray[2]};

    trainingTask(input);
    TEST_ASSERT_EQUAL_MESSAGE(expectedValidData,validData, "validData and its expected value doesnt match");
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expectedOutput, outputArray, 3, "Arrays don't match");
}

void test_OnlyMotorsInvalid()
{
    uint8_t input[3] = {0b00111110, 0b00111110, 0b01010100};
    uint8_t expectedValidData = 0b100;
    uint8_t expectedOutput[3] = {outputArray[0], outputArray[1], input[2]};

    trainingTask(input);
    TEST_ASSERT_EQUAL_MESSAGE(expectedValidData,validData, "validData and its expected value doesnt match");
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expectedOutput, outputArray, 3, "Arrays don't match");
}

