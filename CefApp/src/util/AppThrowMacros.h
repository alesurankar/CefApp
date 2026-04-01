#pragma once
#include <util/AppException.h>

#define APP_EXCEPT(msg) AppException(__LINE__, __FILE__, msg)