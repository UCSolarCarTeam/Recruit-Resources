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
    uint8_t data[3] = {0b00000000, 0b00000000, 0b00111100};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8(0b00000111, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(data, outputArray, 3);
}

void test_EverythingInvalid()
{
    uint8_t data[3] = {0b00111111, 0b10111111, 0b00001101};
    uint8_t expected[3] = {0b11111111, 0b11111111, 0b11111111};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8(0b00000000, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);
}

void test_OnlyLightsInvalid()
{
    uint8_t data[3] = {0b10111111, 0b10111111, 0b00011010};
    uint8_t expected[3] = {0b10111111, 0b10111111, 0b11111111};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8(0b00000011, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);
}

void test_OnlyMotorsInvalid()
{
    uint8_t data[3] = {0b00111111, 0b10111111, 0b00001100};
    uint8_t expected[3] = {0b11111111, 0b11111111, 0b00001100};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8(0b00000100, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);
}
