#include "unity.h"
#include "TrainingTest.h"
#include "Training.h"

void runTrainingTests()
{
    RUN_TEST(test_EverythingValid);
    RUN_TEST(test_EverythingInvalid);
    RUN_TEST(test_OnlyLightsInvalid);
    RUN_TEST(test_OnlyMotorsInvalid);
}

void test_EverythingValid()
{
  uint8_t inputData [3] = {0b10111111, 0b10011111, 0b00111010};
  uint8_t expectedOutputData[3] = {inputData[0], inputData[1], inputData[2]};
  uint8_t expectedValid = 0b111;
  trainingTask(inputData);
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutputData, outputArray, 3, "Output array did not match expected output array");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE (expectedValid, validData, "Valid data did not match expected valid");
}

void test_EverythingInvalid()
{
  uint8_t inputData [3] = {0b00111111, 0b10011110, 0b00101011};
  uint8_t expectedOutputData[3] = {outputArray[0], outputArray[1], outputArray[2]};
  uint8_t expectedValid = 0b000;
  trainingTask(inputData);
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutputData, outputArray, 3, "Output array did not match expected output array");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE (expectedValid, validData, "Valid data did not match expected valid");
}

void test_OnlyLightsInvalid()
{
  uint8_t inputData [3] = {0b11010110, 0b11011110, 0b00101011};
  uint8_t expectedOutputData[3] = {inputData[0], inputData[1], outputArray[2]};
  uint8_t expectedValid = 0b011;
  trainingTask(inputData);
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutputData, outputArray, 3, "Output array did not match expected output array");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE (expectedValid, validData, "Valid data did not match expected valid");
}

void test_OnlyMotorsInvalid()
{
  uint8_t inputData [3] = {0b00111111, 0b10011110, 0b01001100};
  uint8_t expectedOutputData[3] = {outputArray[0], outputArray[1], inputData[2]};
  uint8_t expectedValid = 0b100;
  trainingTask(inputData);
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutputData, outputArray, 3, "Output array did not match expected output array");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE (expectedValid, validData, "Valid data did not match expected valid");
}
