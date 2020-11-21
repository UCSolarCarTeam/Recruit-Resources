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
    uint8_t inputArray[3] = {0b00000000, 0b00000000, 0b00000001};
    trainingTask(inputArray);
    TEST_ASSERT_EQUAL_MESSAGE(0b00000111, validData, "Data was not 0b00000111");
    TEST_ASSERT_EQUAL_INT8_ARRAY_MESSAGE (inputArray, outputArray, 3, "outputArray was not copied correctly");
}

void test_EverythingInvalid()
{
    uint8_t inputArray[3] = {0b01000011, 0b010000011, 0b00000011};
    uint8_t expectedArray[3] = {outputArray[0], outputArray[1], outputArray[2]};
    trainingTask(inputArray);
    TEST_ASSERT_EQUAL_MESSAGE(0b00000000, validData, "Data was not 0b00000000");
    TEST_ASSERT_EQUAL_INT8_ARRAY_MESSAGE (expectedArray, outputArray, 3, "outputArray should not change.");
}

void test_OnlyLightsInvalid()
{
    uint8_t inputArray[3] = {0b11010010, 0b11010010, 0b00000011};
    uint8_t expectedArray[3] = {inputArray[0], inputArray[1], outputArray[2]};
    trainingTask(inputArray);
    TEST_ASSERT_EQUAL_MESSAGE(0b00000011, validData, "Data was not 0b00000011");
    TEST_ASSERT_EQUAL_INT8_ARRAY_MESSAGE (expectedArray, outputArray, 3,  "Motor information was not copied correctly into outputArray");

}

void test_OnlyMotorsInvalid()
{
    uint8_t inputArray[3] = {0b01000011, 0b010000011, 0b01000010};
    uint8_t expectedArray[3] = {outputArray[0], outputArray[1], inputArray[2]};
    trainingTask(inputArray);
    TEST_ASSERT_EQUAL_MESSAGE(0b00000100, validData, "Data was not 0b00000100");
    TEST_ASSERT_EQUAL_INT8_ARRAY_MESSAGE (expectedArray, outputArray, 3, "Lights information was not copied correctly into outputArray");
}
