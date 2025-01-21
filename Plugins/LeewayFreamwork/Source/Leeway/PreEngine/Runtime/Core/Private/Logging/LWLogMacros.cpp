//--------------------
// kun 2025.01.12
//--------------------

//#include "LWLogMacros.h"
#include "Leeway/PreEngine/Runtime/Core/Public/Logging/LWLogMacros.h"
#include "GenericPlatform/GenericPlatformStackWalk.h"

TCHAR* NSLeeway::GetTraceStack(int SkipDepth, int WalkDepth)
{
#if UE_EDITOR
    static TCHAR Buffer[65535];
    Buffer[0] = TCHAR('\0');
    TArray<FProgramCounterSymbolInfo> Stacks = FPlatformStackWalk::GetStack(SkipDepth, WalkDepth);
    for (int i = 0; i < Stacks.Num(); i++)
    {
        auto& Stack = Stacks[i];
        TCHAR LineBuffer[2048] = { 0 };
        // note by kun 2025.01.13
        // visual studio output format: "$FileName($Line): $Text"
        // TCString<TCHAR>::Snprintf(LineBuffer, sizeof(LineBuffer), TEXT("\n%s(%d): %s"), ANSI_TO_TCHAR(Stack.Filename), Stack.LineNumber, ANSI_TO_TCHAR(Stack.FunctionName));
        TCString<TCHAR>::Snprintf(LineBuffer, sizeof(LineBuffer), TEXT("\n%s (%s:%d)"), ANSI_TO_TCHAR(Stack.FunctionName), ANSI_TO_TCHAR(Stack.Filename), Stack.LineNumber);
        FCString::Strcat(Buffer, LineBuffer);
    }
    return Buffer;
#endif
}