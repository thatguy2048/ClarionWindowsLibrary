!ABCIncludeFile(WindowsExt)

!Redefiend WINDOWS.INC methods to conform with naming scheme

OMIT('_END_OF_CODE_',_WINDOWS_EXTENDED_INC_)
_WINDOWS_EXTENDED_INC_        EQUATE(1)

INCLUDE('WindowsTypes.inc'),ONCE

!Common HRESULT Values, although more can exist https://learn.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values
WIN:HRESULT:VALUE   ITEMIZE,PRE
S_OK                    EQUATE(0)
E_ABORT                 EQUATE(80004004H)
E_ACCESSDENIED          EQUATE(80070005H)
E_FAIL                  EQUATE(80004005H)
E_HANDLE                EQUATE(80070006H)
E_INVALIDARG            EQUATE(80070057H)
E_NOINTERFACE           EQUATE(80004002H)
E_NOTIMPL               EQUATE(80004001H)
E_OUTOFMEMORY           EQUATE(8007000EH)
E_POINTER               EQUATE(80004003H)
E_UNEXPECTED            EQUATE(8000FFFFH)
                    END

WIN:UUID GROUP,TYPE
Data1           ULONG
Data2           USHORT
Data3           USHORT
Data4           STRING(8)
END

    MAP
        MODULE('WinAPI')
            !From WINDOWS.INC
            WIN:CloseHandle(WIN:HANDLE hObject),BOOL,PASCAL,PROC,NAME('CloseHandle')
            WIN:CreateSemaphore(<*SECURITY_ATTRIBUTES lpSemaphoreAttributes>, LONG lInitialCount, LONG lMaximumCount, *WIN:CSTR lpName), LONG, RAW, PASCAL, NAME('CreateSemaphoreA')
            WIN:FindWindow(<*WIN:CSTR lpClassName>, *WIN:CSTR lpWindowName),WIN:HANDLE,PASCAL,RAW,NAME('FindWindowA')            
            WIN:FreeLibrary(WIN:HMODULE hModule),BOOL,PASCAL,PROC,NAME('FreeLibrary')
            WIN:GetDC(WIN:HWND),WIN:HDC,PASCAL,PROC,NAME('GetDC')
            WIN:GetDeviceCaps(WIN:HDC, SIGNED),SIGNED,PASCAL,NAME('GetDeviceCaps')
            !WIN:GetLastError(),LONG,PASCAL,NAME('GetLastError')
            WIN:GetOpenFileName(LONG),pascal,bool,proc,name('GetOpenFileNameA')
            WIN:GetPrivateProfileString(*WIN:CSTR,*WIN:CSTR,*WIN:CSTR,*WIN:CSTR,WIN:DWORD,*WIN:CSTR),WIN:DWORD,PASCAL,RAW,NAME('GetPrivateProfileStringA')
            WIN:GetProcAddress(WIN:HMODULE hModule, *CSTRING szProcName),LONG,PASCAL,RAW,NAME('GetProcAddress')
            WIN:GetSaveFileName(LONG),pascal,bool,proc,name('GetSaveFileNameA')
            WIN:GetSystemMetrics(SIGNED),SIGNED,PASCAL,NAME('GetSystemMetrics')
            WIN:IsIconic(WIN:HWND),BOOL,PASCAL,NAME('IsIconic')
            WIN:LoadLibrary(*CSTRING szLibFileName),WIN:HMODULE,PASCAL,RAW,NAME('LoadLibraryA')
            WIN:PatBlt(WIN:HDC, SIGNED, SIGNED, SIGNED, SIGNED, WIN:DWORD),BOOL,PASCAL,NAME('PatBlt')
            WIN:ReleaseDC(WIN:HWND, WIN:HDC),SIGNED,PASCAL,PROC,NAME('ReleaseDC')
            WIN:RpcStringFree(*CSTRING gotString),LONG,PROC,PASCAL,RAW,NAME('RpcStringFreeA')
            WIN:GetForegroundWindow(),WIN:HWND,PASCAL,NAME('GetForegroundWindow')
            WIN:SetForegroundWindow(WIN:HWND),BOOL,PASCAL,NAME('SetForegroundWindow')
            WIN:SetWindowLong(WIN:HWND,SIGNED,LONG),LONG,PASCAL,NAME('SetWindowLongA')
            WIN:ShellExecute(WIN:HWND hwnd,<*WIN:LPCSTR lpOperation>,*WIN:LPCSTR lpFile,<*WIN:LPCSTR lpParameters>,<*WIN:LPCSTR lpDirectory>,SIGNED nShowCmd),WIN:HINSTANCE,PASCAL,RAW,PROC,NAME('ShellExecuteA')
            WIN:ShowWindow(WIN:HWND, SIGNED nCmdShow),BOOL,PASCAL,NAME('ShowWindow')
            WIN:UuidCreate(*WIN:UUID),LONG,PASCAL,PROC,RAW,NAME('UuidCreate')
            WIN:UuidFromString(LONG addressOfString, *WIN:UUID ret),LONG,PROC,PASCAL,RAW,NAME('UuidFromStringA')
            WIN:UuidToString(*WIN:UUID, *CSTRING resString),LONG,PROC,PASCAL,RAW,NAME('UuidToStringA')  !Returns the address of a CSTRING that must be freed via RpcStringFree
            WIN:WaitForSingleObject(WIN:HANDLE hHandle, LONG dwMilliseconds),LONG,PASCAL,NAME('WaitForSingleObject')

            !Added
            WIN:FormatMessage(WIN:DWORD dwFlags, WIN:LPVOID lpSource, WIN:DWORD dwMessageID, WIN:DWORD dwLanguageID, *CSTRING lpBuffer, WIN:DWORD bufferSize, WIN:LPVOID va_args), WIN:DWORD,PASCAL,RAW,NAME('FormatMessageA'),Dll(dll_mode)  
            WIN:GetCurrentProcessID(),WIN:DWORD,PASCAL,NAME('GetCurrentProcessId')
        END
    END

_END_OF_CODE_