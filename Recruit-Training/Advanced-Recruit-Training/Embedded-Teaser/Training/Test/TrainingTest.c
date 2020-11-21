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
	uint8_t inputData[3] = {0b10101011, 0b10101101, 0b00001010}; 
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (inputData, outputArray, 3, "All input data must be copied to outputArray as all data is valid");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE (7, validData, "validData should have the first 3 bits as 1 as all data inputs are valid");
}

void test_EverythingInvalid()
{
	printf("\nTesting trainingTask - Should Pass\n");
	uint8_t inputData[3] = {0b10011010, 0b01011000, 0b00101110};
	uint8_t expectedOutput[3] = {0};
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutput, outputArray, 3, "outputArray should have all zeros as none of the data inputs is valid");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE (0, validData, "The last 3 bits of validData should remain zero as all data is invalid");
}

void test_OnlyLightsInvalid()
{
	printf("\nTesting trainingTask - Should Pass\n");
	uint8_t inputData[3] = {0b10101011, 0b10101101, 0b00110010};
	uint8_t expectedOutput[3] = {0b10101011, 0b10101101, 0};
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutput, outputArray, 3, "Only motors data should be copied into outputArray as these are valid data while the lights data is invlaid");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE (3, validData, "Bits 0 and 1 of validData should be set to 1 as they represent the motors which have valid inputs");
}

void test_OnlyMotorsInvalid()
{
	printf("\nTesting trainingTask - Should Pass\n");
	uint8_t inputData[3] = {0b10011010, 0b01011000, 0b00001010};
	uint8_t expectedOutput[3] = {0, 0, 0b00001010};
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutput, outputArray, 3, "Only lights data should be copied into outputArray as these are valid data while the motors data is invlaid");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE (4, validData, "Bit 3 of validData should be set to 1 as it represents lights data which is valid");
}
