!ABCIncludeFile(WindowsExt)

!Redefiend WINDOWS.INC methods to conform with naming scheme

NULL                    EQUATE(0)
VOID                    EQUATE(LONG)

WIN:NULL                EQUATE(NULL)

WIN:HANDLE                  EQUATE(LONG)
WIN:HWND                    EQUATE(WIN:HANDLE)
WIN:HINSTANCE               EQUATE(WIN:HANDLE)
WIN:HMODULE                 EQUATE(WIN:HANDLE)
WIN:HMENU                   EQUATE(WIN:HANDLE)
WIN:HDC                     EQUATE(WIN:HANDLE)
WIN:HICON                   EQUATE(WIN:HANDLE)
WIN:HCURSOR                 EQUATE(WIN:HANDLE)
WIN:HBRUSH                  EQUATE(WIN:HANDLE)
WIN:HBITMAP                 EQUATE(WIN:HANDLE)
WIN:HGDIOBJ                 EQUATE(WIN:HANDLE)
WIN:HFONT                   EQUATE(WIN:HANDLE)
WIN:HRGN                    EQUATE(WIN:HANDLE)
WIN:HGLOBAL                 EQUATE(WIN:HANDLE)
WIN:HPEN                    EQUATE(WIN:HANDLE)
WIN:HRESULT                 EQUATE(LONG)
WIN:DWORD                   EQUATE(ULONG)
WIN:VOID                    EQUATE(VOID)

! Not defining pointers, as they are better represented by using *TYPE notation
! LPCSTR                  EQUATE(CSTRING)
! LPSTR                   EQUATE(CSTRING)
! LPVOID                  EQUATE(LONG)
! LPCVOID                 EQUATE(LONG)
! PLONG                   EQUATE(LONG)
WIN:LPVOID                  EQUATE(LONG) !Using *VOID in the function definitions caused errors

!TRUE                    EQUATE(1) !In EQUATES.CLW
!FALSE                   EQUATE(0) !In EQUATES.CLW

WIN:ERROR_CODE              EQUATE(WIN:DWORD) ! Windows error code
WIN:NO_ERROR                EQUATE(0)

WIN:INVALID_HANDLE_VALUE        EQUATE(-1)

WIN:UUID GROUP,TYPE
Data1 ULONG
Data2 USHORT
Data3 USHORT
Data4 STRING(8)
END

    MAP
        MODULE('WinAPI')
            !From WINDOWS.INC
            WIN:CloseHandle(WIN:HANDLE hObject),BOOL,PASCAL,PROC,NAME('CloseHandle')
            WIN:CreateSemaphore(<*SECURITY_ATTRIBUTES lpSemaphoreAttributes>, LONG lInitialCount, LONG lMaximumCount, *CSTRING lpName), LONG, RAW, PASCAL, NAME('CreateSemaphoreA')
            WIN:FindWindow(<*CSTRING lpClassName>, *CSTRING lpWindowName),UNSIGNED,PASCAL,RAW,NAME('FindWindowA')
            WIN:FreeLibrary(WIN:HMODULE hModule),BOOL,PASCAL,PROC,NAME('FreeLibrary')
            WIN:GetDC(WIN:HWND),WIN:HDC,PASCAL,PROC,NAME('GetDC')
            WIN:GetDeviceCaps(WIN:HDC, SIGNED),SIGNED,PASCAL,NAME('GetDeviceCaps')
            WIN:GetLastError(),LONG,PASCAL,NAME('GetLastError')
            WIN:GetOpenFileName(LONG),pascal,bool,proc,name('GetOpenFileNameA')
            WIN:GetPrivateProfileString(*WIN:LPCSTR,*WIN:LPCSTR,*WIN:LPCSTR,*WIN:LPCSTR,WIN:DWORD,*WIN:LPCSTR),WIN:DWORD,PASCAL,RAW,NAME('GetPrivateProfileStringA')
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

