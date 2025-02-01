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
    TArray<FProgramCounterSymbolInfo> Stacks = FGenericPlatformStackWalk::GetStack(SkipDepth, WalkDepth);
    FCString::Strcat(Buffer, TEXT("\n\nC++ Call Stack:"));
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

    FString BPCallStack = FFrame::GetScriptCallstack();
    FCString::Strcat(Buffer, *BPCallStack);

    return Buffer;
#endif
}

//inline NSLeeway::FLWIntACC::FLWIntACC(const TCHAR* Name, uint32 Mod, uint32 Flags)
//    :FAutoConsoleCommandWithWorldArgsAndOutputDevice(Name
//        , Text_LogLevelHelp
//        , FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateSP(this, FLWIntACC::Command)
//        , Flags)
//{
//}
//
//inline void NSLeeway::FLWIntACC::Command(const TArray<FString>& Args, UWorld* World, FOutputDevice& Output)
//{
//    if (Args.IsValidIndex(0))
//    {
//        if (!Args[0].IsEmpty())
//        {
//            LexFromString(ASCLogLevel, *Args[0]);
//            return;
//        }
//    }
//
//    if (Mod > 0)
//    {
//        Value = (Value + 1) % Mod;
//    }
//    else
//    {
//        Value = 0;
//    }
//}
