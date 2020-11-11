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
	printf("\nTesting trainingTask - Should Pass\n");
	uint8_t inputData[3] = {0b11001011, 0b11010111, 0b00001010}; 
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY (inputData, outputArray, 3);
	TEST_ASSERT_EQUAL_UINT8 (7, validData);
}

void test_EverythingInvalid()
{
	printf("\nTesting trainingTask - Should Pass\n");
	uint8_t inputData[3] = {0b01001011, 0b11010110, 0b01011101};
	uint8_t expectedOutput[3] = {0};
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY (expectedOutput, outputArray, 3);
	TEST_ASSERT_EQUAL_UINT8 (0, validData);
}

void test_OnlyLightsInvalid()
{
	printf("\nTesting trainingTask - Should Pass\n");
	uint8_t inputData[3] = {0b11001011, 0b11010111, 0b01011101};
	uint8_t expectedOutput[3] = {0};
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY (expectedOutput, outputArray, 3);
	TEST_ASSERT_EQUAL_UINT8 (3, validData);
}

void test_OnlyMotorsInvalid()
{
	printf("\nTesting trainingTask - Should Pass\n");
	uint8_t inputData[3] = {0b01001011, 0b11010110, 0b00001010};
	uint8_t expectedOutput[3] = {0};
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY (expectedOutput, outputArray, 3);
	TEST_ASSERT_EQUAL_UINT8 (4, validData);
}

