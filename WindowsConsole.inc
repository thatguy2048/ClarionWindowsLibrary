!ABCIncludeFile(Console)

OMIT('_END_OF_CODE_',_WINDOWS_CONSOLE_INC_)
_WINDOWS_CONSOLE_INC_        EQUATE(1)

    INCLUDE('WindowsExtended.inc'),ONCE    
    INCLUDE('WindowsHandle.inc'),ONCE

!IO Handle
WIN:CON:STD_HANDLE  ITEMIZE,PRE
INPUT                   EQUATE(-10)
OUTPUT                  EQUATE(-11)
ERROR                   EQUATE(-12)
                    END

!Input Console Mode Flags https://learn.microsoft.com/en-us/windows/console/setconsolemode
WIN:CON:INPUT_MODE_FLAGS    ITEMIZE,PRE
ECHO_INPUT                      EQUATE(0004h)
INSERT_MODE                     EQUATE(0020h)
LINE_INPUT                      EQUATE(02h)
MOUSE_INPUT                     EQUATE(0010h)
PROCESSED_INPUT                 EQUATE(01h)
QUICK_EDIT_MODE                 EQUATE(040h)
WINDOW_INPUT                    EQUATE(0008h)
VIRTUAL_TERMINAL_INPUT          EQUATE(0200h)
                            END

!Output Console Mode Flags
WIN:CON:OUTPUT_MODE_FLAGS   ITEMIZE,PRE
PROCESSED_OUTPUT                EQUATE(0001h)
WRAP_AT_EOL_OUTPUT              EQUATE(0002h)
VIRTUAL_TERMINAL_PROCESSING     EQUATE(0004h)
DISABLE_NEWLINE_AUTO_RETURN     EQUATE(0008h)
LVB_GRID_WORLDWIDE              EQUATE(0010h)
                            END


WIN:CON:NEW_LINE_STR            CSTRING('<13,10>') !/r/n new line

                    MAP
                        MODULE('WinConsoleAPI') ! Some common API functions
                            WIN:CON:SetTitle(*CSTRING titleStr),BOOL,PROC,RAW,PASCAL,NAME('SetConsoleTitleA') ! Sets the title for the current console window.
                            WIN:CON:GetTitle(*CSTRING outputTitleBuffer, WIN:DWORD outputTitleBufferSize),BOOL,RAW,PASCAL,NAME('GetConsoleTitleA') ! Retrieves the title for the current console window.
                        END
                        MODULE('WindowsConsole.CLW')
                            WIN:CON:AttachOrCreate(),BOOL,PROC
                            WIN:CON:Initialize(),BOOL
                        END
                    END

WIN:CON:_Base  CLASS(WIN:HAN:Scoped),MODULE('WindowsConsole.CLW'), LINK('WindowsConsole.CLW',_ABCLinkMode_), TYPE
byteCount               ULONG

Construct               PROCEDURE()
Destruct                PROCEDURE()
hasValidHandle          PROCEDURE(), BOOL
init                    PROCEDURE(WIN:HANDLE), BOOL
getByteCount            PROCEDURE(), ULONG
setMode          PROCEDURE(WIN:DWORD modeFlag), BOOL, PROC
getMode          PROCEDURE(*WIN:DWORD outModeFlag), BOOL, PROC
addMode          PROCEDURE(WIN:DWORD modeFlag), BOOL, PROC ! Adds a console mode flag to the current console mode
removeMode       PROCEDURE(WIN:DWORD modeFlag), BOOL, PROC ! Removes a console mode flag from the current console mode
                    END


!WIN:CON:Writer      CLASS(WIN:CON:_Base), MODULE('WindowsConsole.CLW'), LINK('WindowsConsole.CLW',_ABCLinkMode_), DLL(_ABCDllMode_), TYPE
WIN:CON:Writer      CLASS(WIN:CON:_Base), MODULE('WindowsConsole.CLW'), LINK('WindowsConsole.CLW',_ABCLinkMode_), TYPE
Construct                       PROCEDURE()
Destruct                        PROCEDURE()
init                            PROCEDURE(), BOOL,PROC
getBytesWritten                 PROCEDURE(), ULONG
write                           PROCEDURE(CONST *CSTRING buffer, WIN:DWORD bufferLength), BOOL, PROC
write                           PROCEDURE(CONST *STRING strToWrite), BOOL, PROC
write                           PROCEDURE(CONST *CSTRING strToWrite), BOOL, PROC
write                           PROCEDURE(STRING strToWrite), BOOL, PROC
writeLine                       PROCEDURE(), BOOL, PROC
writeLine                       PROCEDURE(CONST *CSTRING strToWrite, WIN:DWORD textLength), BOOL, PROC
writeLine                       PROCEDURE(CONST *CSTRING strToWrite), BOOL, PROC
writeLine                       PROCEDURE(CONST *STRING strToWrite) ,BOOL,PROC
writeLine                       PROCEDURE(STRING strToWrite), BOOL, PROC
                    END

WIN:CON:Reader      CLASS(WIN:CON:_Base), MODULE('WindowsConsole.CLW'), LINK('WindowsConsole.CLW',_ABCLinkMode_), TYPE
init                            PROCEDURE (),BOOL,PROC
getBytesRead                    PROCEDURE(),ULONG
read                            PROCEDURE(*CSTRING outputBuffer, WIN:DWORD bufferLength),BOOL,PROC
readLine 			            PROCEDURE (),STRING
                    END



WIN:CON:ConsoleRW   CLASS, MODULE('WindowsConsole.CLW'), LINK('WindowsConsole.CLW',_ABCLinkMode_), TYPE
writer                  &WIN:CON:Writer
reader                  &WIN:CON:Reader

Construct               PROCEDURE()
Destruct                PROCEDURE()
init                    PROCEDURE (),BOOL
askForInput             PROCEDURE(STRING question) STRING, PROC ! Print the question to the console then wait for a response
                    END


_END_OF_CODE_