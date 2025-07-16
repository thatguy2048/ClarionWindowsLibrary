!ABCIncludeFile(Console)

    INCLUDE('WindowsExtended.inc'),ONCE    


!IO Handle
WIN:CON:STD_INPUT_HANDLE    EQUATE(-10)
WIN:CON:STD_OUTPUT_HANDLE   EQUATE(-11)
WIN:CON:STD_ERROR_HANDLE    EQUATE(-12)

!Input Console Mode Flags https://learn.microsoft.com/en-us/windows/console/setconsolemode
WIN:CON:ENABLE_ECHO_INPUT               EQUATE(0004h)
WIN:CON:ENABLE_INSERT_MODE              EQUATE(0020h)
WIN:CON:ENABLE_LINE_INPUT               EQUATE(02h)
WIN:CON:ENABLE_MOUSE_INPUT              EQUATE(0010h)
WIN:CON:ENABLE_PROCESSED_INPUT          EQUATE(01h)
WIN:CON:ENABLE_QUICK_EDIT_MODE          EQUATE(040h)
WIN:CON:ENABLE_WINDOW_INPUT             EQUATE(0008h)
WIN:CON:ENABLE_VIRTUAL_TERMINAL_INPUT   EQUATE(0200h)

!Output Console Mode Flags
WIN:CON:ENABLE_PROCESSED_OUTPUT             EQUATE(0001h)
WIN:CON:ENABLE_WRAP_AT_EOL_OUTPUT           EQUATE(0002h)
WIN:CON:ENABLE_VIRTUAL_TERMINAL_PROCESSING  EQUATE(0004h)
WIN:CON:DISABLE_NEWLINE_AUTO_RETURN         EQUATE(0008h)
WIN:CON:ENABLE_LVB_GRID_WORLDWIDE           EQUATE(0010h)

WIN:CON:NEW_LINE_STR            CSTRING('<13,10>') !/r/n new line

                    MAP
                        MODULE('Console.CLW')
                            WIN:CON:AttachOrCreateConsole(),BOOL,PROC
                            WIN:CON:InitializeConsole(),BOOL
                        END
                    END

WIN:CON:_Base  CLASS,MODULE('Console.CLW'), TYPE
handle                  WIN:HANDLE(WIN:INVALID_HANDLE_VALUE)
byteCount               ULONG

Construct               PROCEDURE()
Destruct                PROCEDURE()
hasValidHandle          PROCEDURE(), BOOL
init                    PROCEDURE(WIN:HANDLE), BOOL
getByteCount            PROCEDURE(), ULONG
setConsoleMode          PROCEDURE(WIN:DWORD modeFlag), BOOL, PROC
getConsoleMode          PROCEDURE(*WIN:DWORD outModeFlag), BOOL, PROC
addConsoleMode          PROCEDURE(WIN:DWORD modeFlag), BOOL, PROC ! Adds a console mode flag to the current console mode
removeConsoleMode       PROCEDURE(WIN:DWORD modeFlag), BOOL, PROC ! Removes a console mode flag from the current console mode
                    END


!WIN:CON:Writer      CLASS(WIN:CON:_Base), MODULE('Console.CLW'), LINK('Console.CLW',_ABCLinkMode_), DLL(_ABCDllMode_), TYPE
WIN:CON:Writer      CLASS(WIN:CON:_Base), MODULE('Console.CLW'), LINK('Console.CLW',_ABCLinkMode_), TYPE
Construct                       PROCEDURE()
Destructor                      PROCEDURE()
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

WIN:CON:Reader      CLASS(WIN:CON:_Base), MODULE('Console.CLW'), LINK('Console.CLW',_ABCLinkMode_), TYPE
init                            PROCEDURE (),BOOL,PROC
!init                            PROCEDURE (BOOL enableLineInput),BOOL,PROC !set the console mode to line input if enableLineInput is true
getBytesRead                    PROCEDURE(),ULONG
read                            PROCEDURE(*CSTRING outputBuffer, WIN:DWORD bufferLength),BOOL,PROC
readLine 			            PROCEDURE (),STRING
                    END



WIN:CON:ConsoleRW   CLASS, MODULE('Console.CLW'), LINK('Console.CLW',_ABCLinkMode_), TYPE
writer                  &WIN:CON:Writer
reader                  &WIN:CON:Reader

Construct               PROCEDURE()
Destruct                PROCEDURE()
init                    PROCEDURE (),BOOL
askForInput             PROCEDURE(STRING question) STRING, PROC ! Print the question to the console then wait for a response
                    END


