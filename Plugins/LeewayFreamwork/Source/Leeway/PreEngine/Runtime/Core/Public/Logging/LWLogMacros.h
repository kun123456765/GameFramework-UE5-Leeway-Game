//--------------------
// kun 2025.01.12
//--------------------

#pragma once

#include "Logging/LogMacros.h"

namespace NSLeeway
{
    TCHAR* GetTraceStack(int SkipDepth = 1, int WalkDepth = 15);
}

#define UE_LOG_EX(CategoryName, Verbosity, Format, ...)\
        UE_LOG(CategoryName, Verbosity, TEXT("[pie=%d, f=%d][%s:%d] ") Format, int32(GPlayInEditorID), GFrameNumber, ANSI_TO_TCHAR(__FUNCTION__), __LINE__, ##__VA_ARGS__)

#define UE_LOG_EX_STACK(CategoryName, Verbosity, Format, ...)\
        UE_LOG_EX(CategoryName, Verbosity, TEXT("[pie=%d, f=%d][%s:%d] ") Format TEXT("%s"), int32(GPlayInEditorID), GFrameNumber, ANSI_TO_TCHAR(__FUNCTION__), __LINE__, ##__VA_ARGS__, NSLeeway::GetTraceStack());

#define UE_CLOG_EX(LogLevel, CategoryName, Verbosity, Format, ...)\
        {\
            if (LogLevel > 1)\
            {\
                UE_LOG_EX_STACK(CategoryName, Verbosity, Format, ##__VA_ARGS__); \
            }\
            else if (LogLevel > 0)\
            {\
                UE_LOG_EX(CategoryName, Verbosity, Format, ##__VA_ARGS__); \
            }\
        }