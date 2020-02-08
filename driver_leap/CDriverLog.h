#pragma once

class CDriverLog final
{
    static vr::IVRDriverLog *ms_pLogFile;

    CDriverLog() = delete;
    ~CDriverLog() = delete;
    CDriverLog(const CDriverLog &that) = delete;
    CDriverLog& operator=(const CDriverLog &that) = delete;

    static void LogVarArgs(const char* pMsgFormat, va_list args);
public:
    static bool Initialize(vr::IVRDriverLog* pDriverLog);
    static void Cleanup();

    static void Log(const char* pMsgFormat, ...);
};
