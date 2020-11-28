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
	uint8_t inputData[3] = {0b10101011, 0b10101101, 0b00001010}; 
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (inputData, outputArray, 3, "One or more datainput wasn't copied to oytputArray");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE (7, validData, "Not all 3 bit of validData are 1");
}

void test_EverythingInvalid()
{
	uint8_t inputData[3] = {0b10011010, 0b01011000, 0b00101110};
	uint8_t expectedOutput[3] = {0};
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutput, outputArray, 3, "oytputArray is not all zeros");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE (0, validData, "last 3 bits of validData are not zero");
}

void test_OnlyLightsInvalid()
{
	uint8_t inputData[3] = {0b10101011, 0b10101101, 0b00110010};
	uint8_t expectedOutput[3] = {0b10101011, 0b10101101, 0};
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutput, outputArray, 3, "motors data should be copied to outputArray but not lights data");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE (3, validData, "Bits 0 and 1 of validData should be set to 1");
}

void test_OnlyMotorsInvalid()
{
	uint8_t inputData[3] = {0b10011010, 0b01011000, 0b00001010};
	uint8_t expectedOutput[3] = {0, 0, 0b00001010};
	trainingTask (inputData);
	TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (expectedOutput, outputArray, 3, "Only lights data should be copied into outputArray");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE (4, validData, "only bit 3 of validData should be set to 1");
}
