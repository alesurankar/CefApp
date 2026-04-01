#pragma once
#include <util/AppException.h>

#define WND_EXCEPT( hr ) HrException( __LINE__,__FILE__,(hr) )
#define WND_LAST_EXCEPT() HrException( __LINE__,__FILE__,GetLastError() )
#define WND_NOGFX_EXCEPT() NoGfxException( __LINE__,__FILE__ )