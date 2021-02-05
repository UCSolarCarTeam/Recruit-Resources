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
    uint8_t data[3] = {0b0, 0b0, 0b1};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b111, validData, 
        "INVALID validData. CHECK YOUR MOTORS AND LIGHTS INPUTS. THEY SHOULD ALL BE VALID.");
}

void test_EverythingInvalid()
{
    uint8_t data[3] = {0b10000000, 0b0, 0b00001101};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b0, validData, 
        "INVALID validData. CHECK YOUR MOTORS AND LIGHTS INPUTS. THEY SHOULD ALL BE INVALID.");
}

void test_OnlyLightsInvalid()
{
    uint8_t data[3] = {0b10111111, 0b10111111, 0b00011010};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b11, validData, 
        "INVALID validData. CHECK YOUR LIGHTS INPUTS. ONLY MOTORS SHOULD BE VALID.");
}

void test_OnlyMotorsInvalid()
{
    uint8_t data[3] = {0b11111111, 0b11111111, 0b00001100};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b100, validData, 
        "INVALID validData. CHECK YOUR MOTORS INPUTS. ONLY LIGHTS SHOULD BE VALID.");
}
