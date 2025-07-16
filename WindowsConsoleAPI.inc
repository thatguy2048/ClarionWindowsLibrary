! Define the windows console commands that are part of the WIN32 api
! These are in a separate file so the "WIN:CON" 'namespace' is not saturated (unless these functions are needed)

INCLUDE('WindowsExtended.inc'),ONCE

! The possible results from allocating a console with options
WIN:CON:ALLOC:RESULT        ITEMIZE,PRE
NO                              EQUATE(0)
NEWR                            EQUATE(1)
EXISTING                        EQUATE(2)
                            END

! The possible modes to allocate a console window
WIN:CON:ALLOC:MODE  ITEMIZE,PRE
DEFAULT                 EQUATE(0)
NEWM                    EQUATE(1) ! Can't be just "NEW"
NO                      EQUATE(2)
                    END



WIN:CON:ALLOC:OPTIONS       GROUP, TYPE
mode                            WIN:WORD ! The mode WIN:CON:ALLOC:MODE, hopefully it's the same size of object as the windows enumeration ALLOC_CONSOLE_MODE
useShowWindow                   BOOL ! If true, the showWindow parameter is used
ShowWindow                      WIN:WORD ! The show window option, as defined https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
                            END

! https://learn.microsoft.com/en-us/windows/console/small-rect-str
WIN:CON:SMALL_RECT  GROUP, TYPE
left                    WIN:SHORT ! The x coordinate of the upper left corner
top                     WIN:SHORT ! The y coordinate of the upper left corner
right                   WIN:SHORT ! The x coordinate of the lower right corner
bottom                  WIN:SHORT ! The y coordinate of the lower right corner
                    END

    MAP
        MODULE('WinConsoleAPI')
            WIN:CON:Alloc(),BOOL,PASCAL,RAW,NAME('AllocConsole'); ! Allocate a new console and attach this process to it
            WIN:CON:AllocWithOptions(*WIN:CON:ALLOC:OPTIONS options, *WIN:WORD outputAllocResult),WIN:HRESULT,PASCAL,RAW,NAME('AllocConsoleWithOptions'); ! Allocate a new console and attach this process to it
            WIN:CON:Attach(WIN:DWORD dwProcessId = -1),BOOL,PASCAL,RAW,NAME('AttachConsole'); ! Attach this process to a console identified by the id, -1 is the parent process
            WIN:CON:Free(),BOOL,PASCAL,RAW,NAME('FreeConsole'); ! Detach from a console
            WIN:CON:GetStdHandle(WIN:DWORD consoleHandleType),WIN:HANDLE,PASCAL,PROC,RAW,NAME('GetStdHandle') ! Retrieves a handle to the specified standard device (standard input, standard output, or standard error).
            WIN:CON:Write(WIN:HANDLE consoleHandle,CONST *CSTRING buffer, WIN:DWORD bufferLength, *WIN:DWORD outputBytesWritten, WIN:LPVOID reserved = NULL),BOOL,RAW,PASCAL,NAME('WriteConsoleA') ! Writes a character string to a console screen buffer beginning at the current cursor location.  
            WIN:CON:Read(WIN:HANDLE consoleHandle, *CSTRING outputBuffer, WIN:DWORD numberOfCharactersToRead, *WIN:DWORD numberOfCharactersRead, WIN:LPVOID readConsoleConstrolStruct = NULL),BOOL,RAW,PASCAL,PROC,NAME('ReadConsoleA') ! Reads character input from the console input buffer and removes it from the buffer.            
            WIN:CON:SetMode(WIN:HANDLE consoleHandle, WIN:DWORD modeFlag),BOOL,PROC,RAW,PASCAL,NAME('SetConsoleMode') ! Sets the input mode of a console's input buffer or the output mode of a console screen buffer.
            WIN:CON:GetMode(WIN:HANDLE consoleHandle, *WIN:DWORD outputModeFlag),BOOL,RAW,PASCAL,NAME('GetConsoleMode') ! Retrieves the current input mode of a console's input buffer or the current output mode of a console screen buffer.
            WIN:CON:GetCP(),UNSIGNED,RAW,PASCAL,NAME('GetConsoleCP') ! Get the console code page identifier (also a reliable way to determine if the console is attached)
            !WIN:CON:SetWindowInfo(WIN:HANDLE outputConsoleHandle, BOOL isAbsolute, CONST * WIN:CON:SMALL_RECT),BOOL,PROC,PASCAL,RAW,NAME('SetConsoleWindowInfo') ! Set the windows position of an output console
            WIN:CON:SetWindowInfo(WIN:HANDLE outputConsoleHandle, BOOL isAbsolute, *WIN:CON:SMALL_RECT),BOOL,PROC,PASCAL,RAW,NAME('SetConsoleWindowInfo') ! Set the windows position of an output console
        END
    END