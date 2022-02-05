#ifndef HEADER_FILE
#define HEADER_FILE

#include "stm32f1xx_hal.h"
//the entire header file file
void TEST_ASSERT_EQUAL_INT32(int32_t expected,int32_t actual);
void TEST_ASSERT_EQUAL_UINT32(uint32_t expected,uint32_t actual);

void TEST_ASSERT_EQUAL_INT(uint32_t expected,int32_t actual);
//void TEST_ASSERT_EQUAL_INT(int32_t expected,uint32_t actual);


#endif
