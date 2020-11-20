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
    uint8_t InputArray[3] = {0b00000000, 0b00000000, 0b00000001};
    trainingTask(InputArray);
    TEST_ASSERT_EQUAL_MESSAGE(0b00000111, validData, "All valid test failed");
}

void test_EverythingInvalid()
{
    uint8_t InputArray[3] = {0b01000011, 0b010000011, 0b00000011};
    trainingTask(InputArray);
    TEST_ASSERT_EQUAL_MESSAGE(0b00000000, validData, "All invalid test failed");

}

void test_OnlyLightsInvalid()
{
    uint8_t InputArray[3] = {0b11010010, 0b11010010, 0b00000011};
    trainingTask(InputArray);
    TEST_ASSERT_EQUAL_MESSAGE(0b00000011, validData, "OnlyLightsInvalid test failed");
}

void test_OnlyMotorsInvalid()
{
   uint8_t InputArray[3] = {0b01000011, 0b010000011, 0b01000010};
   trainingTask(InputArray);
    TEST_ASSERT_EQUAL_MESSAGE(0b00000100, validData, "OnlyMotorsInvalid test failed");
}
