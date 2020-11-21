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
	uint8_t allValidData[] = {  0b10111111,		// Motor on, going forward with positive velocity
								0b10111111,		// Motor on, going forward with positive velocity
								0b01111100 };	// High headlights, with hazards on, brakes off
	trainingTask(allValidData);
	TEST_ASSERT_EQUAL_INT8(validData, 7);		// Expecting 7 for all valid
	TEST_ASSERT_EQUAL_INT8(outputArray[0], 1);	// Expecting 1 for motor 1
	TEST_ASSERT_EQUAL_INT8(outputArray[1], 1);	// Expecting 1 for motor 2
	TEST_ASSERT_EQUAL_INT8(outputArray[2], 1);	// Expecting 1 for lights
}

void test_EverythingInvalid()
{
	uint8_t allValidData[] = {  0b00111111,		// Motor on, going reverse with positive velocity
								0b11111111,		// Motor on, going forward with negative velocity
								0b01100111 };	// Wrong headlights, with hazards on, signals off, brakes off
	trainingTask(allValidData);
	TEST_ASSERT_EQUAL_INT8(validData, 0);		// Expecting 0 for all invalid
	TEST_ASSERT_EQUAL_INT8(outputArray[0], 0);	// Expecting 0 for motor 1
	TEST_ASSERT_EQUAL_INT8(outputArray[1], 0);	// Expecting 0 for motor 2
	TEST_ASSERT_EQUAL_INT8(outputArray[2], 0);	// Expecting 0 for lights
}

void test_OnlyLightsInvalid()
{
	uint8_t allValidData[] = {  0b00000000,		// Motor off
								0b00000000,		// Motor off
								0b01100100 };	// High headlights, with hazards on, signals off, brakes off
	trainingTask(allValidData);
	TEST_ASSERT_EQUAL_INT8(validData, 3);		// Expecting 3 for motors
	TEST_ASSERT_EQUAL_INT8(outputArray[0], 1);	// Expecting 1 for motor 1
	TEST_ASSERT_EQUAL_INT8(outputArray[1], 1);	// Expecting 1 for motor 2
	TEST_ASSERT_EQUAL_INT8(outputArray[2], 0);	// Expecting 0 for lights
}

void test_OnlyMotorsInvalid()
{
	uint8_t allValidData[] = {  0b00000110,		// Motor off, non-zero speed
								0b00011110,		// Motor off, non-zero speed
								0b01010010 };	// Low headlights, with hazards off, one signal on, brakes off
	trainingTask(allValidData);
	TEST_ASSERT_EQUAL_INT8(validData, 4);		// Expecting 4 for lights
	TEST_ASSERT_EQUAL_INT8(outputArray[0], 0);	// Expecting 0 for motor 1
	TEST_ASSERT_EQUAL_INT8(outputArray[1], 0);	// Expecting 0 for motor 2
	TEST_ASSERT_EQUAL_INT8(outputArray[2], 1);	// Expecting 1 for lights
}
