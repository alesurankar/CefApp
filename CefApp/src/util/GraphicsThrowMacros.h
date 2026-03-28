#pragma once

#define GFX_THROW(hrcall, note) \
    do { \
        HRESULT hrTemp = (hrcall); \
        if (FAILED(hrTemp)) \
            throw AppException(__LINE__, __FILE__, note); \
    } while(0)

// macro for importing infomanager into local scope
#ifndef INFOMAN
#define INFOMAN(gfx);
#endif