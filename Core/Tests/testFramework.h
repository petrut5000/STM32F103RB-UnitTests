#ifndef TESTFRAMEWORK
#define TESTFRAMEWORK

#include "stm32f1xx_hal.h"
#include "stdbool.h"

#define TEST_PASSED 'PASSED'
#define TEST_FAILED 'FAILED'

bool UNITTEST_ASSERT_EQUAL_INT32(int32_t expected,int32_t actual);
bool UNITTEST_ASSERT_EQUAL_UINT32(uint32_t expected,uint32_t actual);


#endif
